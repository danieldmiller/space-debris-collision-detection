const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 100000);
const renderer = new THREE.WebGLRenderer({ antialias: true });
const clock = new THREE.Clock();

const spaceHistory = (() => {
	const updateThreshold = 60;
	const cycles = [];
	let dataDone, step;
	let updating = false;

	const cycle = () => cycles[0];
	const objects = () => cycle().objects;
	const time = () => cycle().time;
	const object = id => cycle().objects[id];
	const pull = async () => {
		if (updating)
			return;

		updating = true;
		const response = await fetch('http://localhost:3000/');
		const newCycles = await response.json();

		if (newCycles === false) {
			dataDone = true;
		} else {
			newCycles.forEach(cycle => cycles.push(cycle));
		}

		updating = false;
	};
	const next = () => {
		if (cycles.length < updateThreshold && !dataDone)
			pull();

		if (cycles.length <= 1) {
			if (dataDone)
				init();
			return false;
		} else {
			cycles.shift();
			++step;
			return true;
		}

		return false;
	};
	const init = async () => {
		delete self.init;
		const response = await fetch('http://localhost:3000', { method: 'POST' });
		dataDone = false;
		step = 0;
		await pull();
	};

	const self = {
		step: () => step,
		cycle,
		objects,
		time,
		object,
		next,
		init,
	};

	return self;
})();

const cameraSettings = {
	distance: 100,
	rotation: 0
};

const keys = {};
document.addEventListener('keydown', e => {
	keys[e.key] = true;
});
document.addEventListener('keyup', e => {
	keys[e.key] = false;
});

const init = () => {
	renderer.setSize(window.innerWidth, window.innerHeight);
	document.body.appendChild(renderer.domElement);

	const light = new THREE.PointLight(0xffffff, 1);
	light.position.set(500, 500, 500);
	scene.add(light);
	const ambientLight = new THREE.AmbientLight(0x202020);
	scene.add(ambientLight);
	clock.start();

	const gridHelper = new THREE.GridHelper(1000, 10, '#444444', '#222222');
	gridHelper.position.y = 0;
	scene.add(gridHelper);

	camera.position.y = 50;

	return spaceHistory.init();
};

let cameraPosition = 0;
const animate = () => {
	requestAnimationFrame(animate);
	renderer.render(scene, camera);
	const delta = clock.getDelta();

	if (keys.ArrowUp)
		cameraSettings.distance -= delta * 300;
	if (keys.ArrowDown)
		cameraSettings.distance += delta * 300;
	if (keys.ArrowLeft)
		cameraSettings.rotation -= delta * 2;
	if (keys.ArrowRight)
		cameraSettings.rotation += delta * 2;

	camera.position.x = Math.sin(cameraSettings.rotation) * cameraSettings.distance;
	camera.position.z = Math.cos(cameraSettings.rotation) * cameraSettings.distance;
	camera.lookAt(0, 0, 0);
};

const objects = [];
const addObject = (data, id) => {
	const { r } = data;
	const geometry = new THREE.SphereGeometry(r, 32, 32);
	const material = new THREE.MeshLambertMaterial();
	const mesh = new THREE.Mesh(geometry, material);
	const object = { mesh, id };

	scene.add(mesh);
	objects.push(object);
	updateObject(object, 0);
};

const updateObject = (object) => {
	const data = spaceHistory.object(object.id);
	const { x = 0, y = 0, z = 0 } = data;

	object.mesh.position.set(x, y, z);
};

init().then(() => {
	spaceHistory.objects().forEach((data, i) => addObject(data, i));

	const timeInfo = document.getElementById("time");
	const interval = setInterval(() => {
		if (!spaceHistory.next())
			return;

		timeInfo.innerText = spaceHistory.step();
		objects.forEach(object => updateObject(object));
	}, 1000 / 30);

	animate();
});
