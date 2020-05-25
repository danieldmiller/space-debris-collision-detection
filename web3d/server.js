const child_process = require('child_process');
const express = require('express');
const cors = require('cors');

const program = process.argv[2];
const args = process.argv.slice(3);

if (!program || program.length == 0) {
  console.error('Invalid filename, please provide the executable filename as parameter.');
  process.exit(1);
}

class BaseWrapper {
  read() {
    if (this.fifo.length == 0)
      return false;

    const cycles = [];

    for (let i = 0; i < 60 * 2; i++)
      cycles.push(this.fifo.shift());

    return cycles.filter(Boolean);
  }

  pull() {}
}

class JsonWrapper extends BaseWrapper {
  constructor() {
    super();
    this.fifo = [ ...require('./' + program) ];
  }
}

class Wrapper extends BaseWrapper {
  constructor() {
    super();
    this.cycle = 0;
    this.done = false;
    this.fifo = [];
    this.currentLine = '';

    this.child = child_process.spawn(program, ['--print-objects', '--interactive', ...args]);
    this.child.stdout.on('data', data => this.receive(data));
  }

  pull() {
    if (this.done)
      return;
    try {
      this.child.stdin.write('.\n');
    } catch(e) {
      this.done = true;
    }
  }

  receive(data) {
    this.currentLine += ('' + data);
    if (this.currentLine[this.currentLine.length - 1] != '\n')
      return;

    this.currentLine.split('\n').forEach(data => {
      if (data == '')
        return;

      if (!data.startsWith('{"time":')) {
        console.log(data);
        return;
      }

      this.fifo.push(JSON.parse(data));
      ++this.cycle;
      // console.log(`fifo length = ${this.fifo.length}, cycle = ${this.cycle}`);
    });

    this.currentLine = '';

    if (this.fifo.length < 60 * 5)
      this.pull();
  }
}

let simulation;

const app = express();

app.use(cors());

app.get('/', (req, res) => {
  const payload = simulation.read();

  res.send(payload);
  simulation.pull();
});

app.post('/', (req, res) => {
  simulation = program.split('.').pop() == 'json'
    ? new JsonWrapper()
    : new Wrapper();
  res.send();
});

app.listen(3000, () => {
  console.log('Server listening on port 3000!')
});
