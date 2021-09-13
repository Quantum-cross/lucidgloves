hallthick = 1.60;
hallheight = 5.50;
hallwidth = 4.0 + 1;

halloffset = 27.49;

wallthick = .76;
wallthick2 = 1.51;

pitch = 4.25;

hallsep = floor(hallwidth/pitch)*pitch+(pitch/4);

//magnetthick = .75;
magnetthick = 1.51+.6;

length = 50;

// channel outer wall
translate([0,0])
cube([length, wallthick, hallheight]);

//channel inner wall
//translate([0,wallthick+magnetthick])
//cube([length/2+hallwidth*1.2+wallthick, wallthick/2, hallheight]);

//thicken inner wall
translate([0,wallthick+magnetthick])
cube([-wallthick-hallwidth+25/2+halloffset, wallthick, hallheight]);

translate([-wallthick-hallwidth+25/2+halloffset, wallthick+magnetthick])
cube([hallsep+hallwidth,wallthick/2, hallheight]);

translate([-wallthick+hallsep+25/2+halloffset,wallthick+magnetthick])
cube([-wallthick-hallwidth+length-16-halloffset, wallthick, hallheight]);



//z=0 floor
translate([0,0,-wallthick])
cube([length, wallthick*1.5 + hallthick+magnetthick, wallthick]);

//z=max ceiling
translate([0,0,hallheight])
cube([length, wallthick2+magnetthick, wallthick]);

translate([-wallthick-hallwidth+25/2+halloffset,wallthick*1.5+magnetthick]){
    
    // first hall endstop
    translate([0,0])
    cube([wallthick, hallthick, hallheight]);

    //second hall stop
    translate([hallwidth,0])
    cube([hallsep-hallwidth+wallthick, hallthick, hallheight]);


    //third end stop
    translate([hallsep,0])
    translate([hallwidth,0])
    cube([wallthick, hallthick, hallheight]);
    topnotch = 1.5;
    translate([wallthick,0, hallheight-topnotch])
    cube([hallwidth-wallthick, hallthick/2, topnotch]);

    translate([hallsep,0])
    translate([wallthick,0, hallheight-topnotch])
    cube([hallwidth-wallthick, hallthick/2, topnotch]);
}

translate([length-wallthick, magnetthick + wallthick,.1])
cube([wallthick, wallthick, hallheight-.3]);


// GUIDE

guidesize=3;
guide_d = 40;
// channel outer wall

translate([hallsep+25/2+halloffset,wallthick*3+magnetthick])
mirror([0,1,0])
difference(){
translate([0,-guidesize,-wallthick])
cube([-wallthick*2-hallwidth+length-16-halloffset, wallthick+guidesize, hallheight+wallthick*2]);
translate([-.5,-guide_d/2-.60,hallheight/2])
rotate([0,90,0])
cylinder(d=guide_d, h=length+1, $fn=128);
}

translate([0,wallthick*3+magnetthick])
mirror([0,1,0])
difference(){
translate([0,-guidesize,-wallthick])
cube([-wallthick-hallwidth+25/2+halloffset, wallthick+guidesize, hallheight+wallthick*2]);
translate([-.5,-guide_d/2-.60,hallheight/2])
rotate([0,90,0])
cylinder(d=guide_d, h=length+1, $fn=128);
}

// RAMP

//ramp_r = 15;
//
//translate([0,-ramp_r+wallthick*2+magnetthick, -wallthick]){
//    
//difference(){
//
//    intersection(){
//        cylinder(h=hallheight+wallthick*2, r=ramp_r, $fn=64);
//        translate([-ramp_r,0])
//        cube([ramp_r,ramp_r, 100]);
//            rotate([0,0,20])
//        cube([ramp_r,ramp_r, 10]);
//    }
//    translate([0,0,wallthick])
//    cylinder(h=hallheight, r=ramp_r-wallthick, $fn=64);
//    translate([-ramp_r+1,wallthick-magnetthick-wallthick*3, -wallthick*2])
//cube([ramp_r, ramp_r, hallheight+wallthick*6]);
//    
//    }
//}


