const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer({ antialias: true });

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
	const geometry = new THREE.SphereGeometry(1, 32, 32);
	const material = new THREE.MeshLambertMaterial();
	const mesh = new THREE.Mesh(geometry, material);
	const object = { mesh, id };

	scene.add(mesh);
	objects.push(object);
	updateObject(object, 0);
};

const updateObject = (object, step) => {
	const data = window.spaceHistory[step].objects[object.id];
	const { x = 0, y = 0, z = 0 } = data;

	object.mesh.position.set(x, y, z);
};

init();

if (window.spaceHistory) {
	window.spaceHistory[0].objects.forEach((data, i) => addObject(i));

	let currentStep = 0;
	setInterval(() => {
		currentStep = (currentStep + 1) % window.spaceHistory.length;
		objects.forEach(object => updateObject(object, currentStep));

		const objectPosition = objects[0].mesh.position;
		camera.lookAt(objectPosition);
	}, 1000 / 30);
} else {
	alert('No history found');
}

animate();
