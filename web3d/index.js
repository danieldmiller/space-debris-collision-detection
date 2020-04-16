const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer({ antialias: true });
const clock = new THREE.Clock();
const spaceHistory = window.spaceHistory;

const cameraSettings = {
	distance: 100,
	speed: 0.2
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
	const axesHelper = new THREE.AxesHelper(3);
	scene.add(axesHelper);

	camera.position.y = 25;

};

let cameraPosition = 0;
const animate = () => {
	requestAnimationFrame(animate);
	renderer.render(scene, camera);
	const delta = clock.getDelta();

	if (keys.ArrowUp)
		cameraSettings.distance -= delta * 50;
	if (keys.ArrowDown)
		cameraSettings.distance += delta * 50;
	if (keys.ArrowLeft)
		cameraSettings.speed -= delta * 2;
	if (keys.ArrowRight)
		cameraSettings.speed += delta * 2;

	cameraPosition += delta * cameraSettings.speed;
	camera.position.x = Math.sin(cameraPosition) * cameraSettings.distance;
	camera.position.z = Math.cos(cameraPosition) * cameraSettings.distance;
	camera.lookAt(0, 0, 0);
};

const objects = [];
const addObject = id => {
	const { r } = spaceHistory[0].objects[id];
	const geometry = new THREE.SphereGeometry(r, 32, 32);
	const material = new THREE.MeshLambertMaterial();
	const mesh = new THREE.Mesh(geometry, material);
	const object = { mesh, id };

	scene.add(mesh);
	objects.push(object);
	updateObject(object, 0);
};

const updateObject = (object, step) => {
	const data = spaceHistory[step].objects[object.id];
	const { x = 0, y = 0, z = 0 } = data;

	object.mesh.position.set(x, y, z);
};

init();

if (spaceHistory) {
	spaceHistory[0].objects.forEach((data, i) => addObject(i));

	let currentStep = 0;
	const timeInfo = document.getElementById("time");
	setInterval(() => {
		currentStep = (currentStep + 1) % spaceHistory.length;
		timeInfo.innerText = `${currentStep + 1} / ${spaceHistory.length}`;
		objects.forEach(object => updateObject(object, currentStep));
	}, 1000 / 30);
} else {
	alert('No history found');
}

animate();
