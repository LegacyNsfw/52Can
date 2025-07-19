$fn = 50;

podRadius = 52/2;
podDepth = 20;
podHoleRadius = 23;
bezelRadius = podRadius + 5;
bezelHeight = 10;

// Adafruit 1.8" display with EYESPI
boardWidth = 57;
boardDepth = 36;
boardThickness = 6.5;
holeX = 25.5;
holeY = 15;
cornerRadius = 6;

boltPosition = 21;

/*
// zio.cc 1.5"
screenWidth = 30;
screenDepth = 34;
screenThickness = 1.5;

boardWidth = 45;
boardDepth = 36;
boardThickness = 1;
*/

module top()
{
    difference() {
        hull() {
            translate([0, 0, bezelHeight / 2])
                cylinder(h = bezelHeight, r = bezelRadius, center = true);
            
            translate([holeX, holeY, bezelHeight / 2])
                cylinder(h = bezelHeight, r = cornerRadius, center = true);
            translate([-holeX, holeY, bezelHeight / 2])
                cylinder(h = bezelHeight, r = cornerRadius, center = true);
            translate([holeX, -holeY, bezelHeight / 2])
                cylinder(h = bezelHeight, r = cornerRadius, center = true);
            translate([-holeX, -holeY, bezelHeight / 2])
                cylinder(h = bezelHeight, r = cornerRadius, center = true);
        }
        
        translate([holeX, holeY, 0])
            cylinder(h = bezelHeight, r = 1, center = true);
        translate([-holeX, holeY, 0])
            cylinder(h = bezelHeight, r = 1, center = true);
        translate([holeX, -holeY, 0])
            cylinder(h = bezelHeight, r = 1, center = true);
        translate([-holeX, -holeY, 0])
            cylinder(h = bezelHeight, r = 1, center = true);
        
        // cutout
        translate([0, 0, 2.9])
            cube([boardWidth, 25, 6], center = true);

        // bolts
        translate([0, boltPosition, 0])
            cylinder(h = 100, r = 1.7, center = true);
        translate([0, -boltPosition, 0])
            cylinder(h = 100, r = 1.7, center = true);

        // bolt heads
        translate([0, boltPosition, 9])
            cylinder(h = 3, r = 2.5, center = true);
        translate([0, -boltPosition, 9])
            cylinder(h = 3, r = 2.5, center = true);

        // ribbon connector
        translate([0, 15, 3])
            cube([15, 6, 3], center = true);
    }    

}

module display()
{
    translate([0, 0, boardThickness / 2])
        cube([boardWidth, boardDepth, boardThickness], center = true);
}

module base()
{
    difference() {
        union () {
            // bolt bosses
            translate([0, boltPosition, -podDepth / 2])
                cylinder(h = podDepth, r = 4, center = true);
            translate([0, -boltPosition, -podDepth / 2])
                cylinder(h = podDepth, r = 4, center = true);
            
            // crossbar
            translate([0, 0, -podDepth + 2.5])
                rotate([0, 0, 90])
                cube([podRadius * 2 - 2, 5, 5], center = true);
            
            // sleeve
            difference(){
                union () {
                    translate([0, 0, -podDepth / 2])
                        cylinder(h = podDepth, r = podRadius, center = true);
                }
                cylinder (h = 100, r = podHoleRadius, center = true);
            }
        }
        
        // bolt holes
        translate([0, boltPosition, 0])
            cylinder(h = 100, r = 1.2, center = true);
        translate([0, -boltPosition, 0])
            cylinder(h = 100, r = 1.2, center = true);
    }
}

// You'll probably want to comment out the top() or bottom() to print them separately.
difference() {
    union () {
        //top();
        base();
    }
    translate([0, 0, 4])
        display();
}