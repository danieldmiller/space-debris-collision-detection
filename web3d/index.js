const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer({ antialias: true });
const spaceHistory = window.spaceHistory;

const init = () => {
	renderer.setSize(window.innerWidth, window.innerHeight);
	document.body.appendChild(renderer.domElement);

	const light = new THREE.PointLight(0xffffff, 1);
	light.position.set(50, 50, 50);
	scene.add(light);
	const ambientLight = new THREE.AmbientLight(0x101010);
	scene.add(ambientLight);

	camera.position.z = 50;
	camera.position.y = 25;
	camera.position.x = 25;
	camera.lookAt(0, 0, 0);
};

const animate = () => {
	requestAnimationFrame(animate);
	renderer.render(scene, camera);
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
