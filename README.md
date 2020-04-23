# space-debris-collision-detection
High performance parallel algorithm for detecting debris collision

## Flags

To show the help, run `./space-debris-collision-detection --help`. There is several flags that will allow you to customize the simulation and the way it's run.

- `-p` or `--print-objects`: Prints a json with information on the `SpaceObjects` at each cycle.
- `-o` or `--objects <n>`: The number of `SpaceObjects` to simulate.
- `-c` or `--cycles <n>`: The number of cycles to simulate (one iteration of the for loop in the `Space::update` method is a cycle).
- `-i` or `--interactive`: Wait for a user input between each step. You need to write at least one character. For instance, write `.` and then press enter.
- `-h` or `--help`: Shows the help.

## Web 3D visualisation

### Installation and usage

In the folder `web3d`, you can find several `.js` files and on `index.html` file. It is used the visualize the simulation in 3D directly in your browser. To use it, you will need [node.js](https://nodejs.org).

It is composed in two parts, the server, and the client. The server just take care of running the simulation program with the flags `--print-objects` and `--interactive`, and expose an api for the client to get the consecutive steps.

To run the visualixation, please follow those steps:

- Run `npm install` to install the server's dependencies. (npm should be automatically installed with node.js)
- Run `node server.js <path_to_your_excutable> <options>` to start the server. For instance `node server.js ../space-debris-collision-detection -o 100 -c 2000`.
- Once the server is up and running, you can open `index.html` in your browser. And you should see the simulation.

A new simulation is automatically started every time the previous one is done, or when the page is refreshed. Thus, if you do any changes on the simulation program you don't need to restart the server, but only to restart the web page.

Please don't open several tabs with the visualiation, since it's using the same data, it will interfer together and could results in weird behaviors (for instance, a simulation restarting randomly).

### Controls

Once you are in the simulation, you can use the arrow keys to move around the center of the world, or to get closer / further.
