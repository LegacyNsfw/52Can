boardRadius = 25;
boltRadius = 1.3;
boltPosition = 21;
reliefRadius = 2.5;

$fn = 100;

projection()
translate([0, 0, 10])
difference()
{
    // plate
    cylinder(h = 1, r1 = boardRadius, r2 = boardRadius, center = true);
    
    // mounting bolts
    translate([boltPosition, 0, 0])
        cylinder(h = 2, r1 = boltRadius, r2 = boltRadius, center = true);
    translate([-boltPosition, 0, 0])
        cylinder(h = 2, r1 = boltRadius, r2 = boltRadius, center = true);
    
    // strain relief
    translate([0, 15, 0])
    {
        cylinder(h = 2, r1 = reliefRadius, r2 = reliefRadius, center = true);
        translate([10, 0, 0])
            cylinder(h = 2, r1 = reliefRadius, r2 = reliefRadius, center = true);
        translate([-10, 0, 0])
            cylinder(h = 2, r1 = reliefRadius, r2 = reliefRadius, center = true);           
    }
}