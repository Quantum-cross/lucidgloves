// This file is created by Robert Cross <@Quantum-cross> as a modification of
// LucidVR/lucidgloves which is released under the MIT License.
// See file LICENSE for details.

hallthick = 1.60;
hallheight = 5.50;
hallwidth = 4.0 + 2;

wallthick = .76;
wallthick2 = 1.51;

magnetthick = 0.70;

length = 25;

cube([length, wallthick2, hallheight]); // "bottom"

// channel inner wall
translate([0,wallthick*2+hallthick])
cube([length/2+hallwidth*1.2+wallthick/2, wallthick/2, hallheight]);

//channel outer wall
translate([0,wallthick*1.5+hallthick + wallthick + magnetthick])
cube([length, wallthick, hallheight]);

//z=0 floor
translate([0,0,-wallthick])
cube([length, wallthick*1.5 + wallthick2*1 + hallthick+magnetthick, wallthick]);

//z=max cieling
translate([0,wallthick*2+hallthick,hallheight])
cube([length, wallthick*1.5+magnetthick, wallthick/2]);

translate([-wallthick/2-hallwidth+length/2,0,0]){
// first hall endstop
translate([0,wallthick2])
cube([wallthick, hallthick, hallheight]);

//second hall stop
translate([hallwidth,wallthick2])
cube([wallthick, hallthick, hallheight]);

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
translate([hallwidth,0])
translate([hallwidth*1.2,wallthick2])
cube([wallthick, hallthick, hallheight]);
}
