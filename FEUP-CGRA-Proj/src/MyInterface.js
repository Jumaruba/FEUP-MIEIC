/**
 * MyInterface
 * @constructor
 */
class MyInterface extends CGFinterface {
    constructor() {
        super();
    }

    init(application) {
        // call CGFinterface init
        super.init(application);
        // init GUI. For more information on the methods, check:
        // http://workshop.chromeexperiments.com/examples/gui
        this.gui = new dat.GUI();

        let obj = this;

        //Checkbox element in GUI
        this.gui.add(this.scene, 'displayAxis').name('Display Axis');
        this.gui.add(this.scene, 'displaySphere').name('Display Sphere');
        this.gui.add(this.scene, 'displaySkybox').name('Display Skybox');
        this.gui.add(this.scene, 'displayTerrain').name('Display Terrain');

        //Dropdown for textures quad
        this.gui.add(this.scene, 'selectedTex', this.scene.textureIds).name('Texture Quad').onChange(this.scene.updateAppliedTex.bind(this.scene));

        //Cylinder folder 
        let f0 = this.gui.addFolder('Cylinder config');
        f0.add(this.scene, 'displayCylinder').name('Display Cylinder');
        f0.add(this.scene, 'enableTexCylinder').name('Cylinder Tex');
        f0.add(this.scene, 'selectedTexCylinder', this.scene.texturesCylinderId).name('Texture Cylinder').onChange(this.scene.updateAppliedTex.bind(this.scene));
        f0.add(this.scene, 'nFaces', 0, 100).name('Cylinder Faces');

      //Vehicle folder
        var f1 = this.gui.addFolder('Vehicle config');
        f1.add(this.scene, 'displayVehicle').name('Display Vehicle');
        f1.add(this.scene,'speedFactor',0.1,3).name('Speed Factor');
        f1.add(this.scene,'accel',0.0,3.0).name('Acceleration');
        f1.add(this.scene,'scaleFactor',0.5,3).name('Scale Factor');

        this.init_keys();
        return true;
    }

    init_keys() {

        this.scene.gui = this;
        this.processKeyboard = function () {
        };
        this.activeKeys = {};
    }

    processKeyDown(event) {
        this.activeKeys[event.code] = true;
    };

    processKeyUp(event) {
        this.activeKeys[event.code] = false;
    };

    isKeyPressed(keyCode) {
        return this.activeKeys[keyCode];
    }
}
