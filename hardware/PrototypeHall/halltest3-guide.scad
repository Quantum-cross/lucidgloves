// This file is created by Robert Cross <@Quantum-cross> as a modification of
// LucidVR/lucidgloves which is released under the MIT License.
// See file LICENSE for details.

hallthick = 1.60;
hallheight = 5.50;
hallwidth = 4.0 + 1;

wallthick = .76;
wallthick2 = 1.51;

magnetthick = 1.0;

length = 10;

//cube([length, wallthick2, hallheight]); // "bottom"

guidesize=3;
guide_d = 19;
// channel outer wall

difference(){
translate([0,-guidesize,-wallthick])
cube([length, wallthick+guidesize, hallheight+wallthick*2]);
translate([-.5,-guide_d/2,hallheight/2])
rotate([0,90,0])
cylinder(d=guide_d, h=length+1, $fn=128);
}

//channel inner wall
translate([0,wallthick+magnetthick])
cube([length, wallthick, hallheight]);

//z=0 floor
translate([0,wallthick,-wallthick])
cube([length, wallthick+magnetthick, wallthick]);

//z=max cieling
translate([0,wallthick,hallheight])
cube([length, wallthick+magnetthick, wallthick]);

//translate([-wallthick-hallwidth+length/2,wallthick*1.5+magnetthick]){
// first hall endstop
//translate([0,0])
//cube([wallthick, hallthick, hallheight]);

//second hall stop
//translate([hallwidth,0])
//cube([wallthick+hallwidth*.1, hallthick, hallheight]);

// first hall triangles
//translate([wallthick, wallthick2]){
//    linear_extrude(hallheight)
//        polygon([[0,0],[0,hallthick/2],[hallthick/2,0]]);
//    translate([hallwidth-wallthick,0])
//        linear_extrude(hallheight)
//            polygon([[-hallthick/2,0],[0,hallthick/2],[0,0]]);
//}

//second hall triangles
//translate([hallwidth,0]){
//translate([wallthick, wallthick2]){
//    linear_extrude(hallheight)
//        polygon([[0,0],[0,hallthick/2],[hallthick/2,0]]);
//    translate([hallwidth*1.2-wallthick,0])
//        linear_extrude(hallheight)
//            polygon([[-hallthick/2,0],[0,hallthick/2],[0,0]]);
//}

//third end stop
//translate([hallwidth*1.1,0])
//translate([hallwidth,0])
//cube([wallthick, hallthick, hallheight]);

//translate([wallthick,0, hallheight-1])
//cube([hallwidth-wallthick, hallthick/2, 1]);

////translate([wallthick+hallwidth*1.1,0, hallheight-1])
//cube([hallwidth-wallthick, hallthick/2, 1]);
//}
