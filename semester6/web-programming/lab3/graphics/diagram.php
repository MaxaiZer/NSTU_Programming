<?php

session_start();
$diagram_data = $_SESSION["diagram_data"];

$size_x = 800;
$size_y = 500;

$im=@imagecreate($size_x, $size_y) or die ("Cant Initialize GD");

imagesavealpha($im, true);
$transparent = imagecolorallocatealpha($im, 0, 0, 0, 127);
imagefill($im, 0, 0, $transparent);

if (count($diagram_data) > 0)
    drawData($im, $size_x, $size_y, $diagram_data);
else {
    $error_color = imagecolorallocate($im, 49, 106, 236);
    imagestring($im, 3, $size_x / 2, $size_y / 2, "Diagram is empty", $error_color);
}

header("Content-Type: image/png");
imagepng($im);

function drawData($im, $size_x, $size_y, $diagram_data) {
    $axis_offset_y = 40;

    $black = imagecolorallocate($im,0,0,0);
    imageline($im, 0, $size_y - $axis_offset_y , $size_x, $size_y - $axis_offset_y , $black);
    imageline($im, 0, 0, 0, $size_y - $axis_offset_y , $black);
    
    $rect_offset = 40;
    $count = count($diagram_data);
    
    $rect_max_size_x = $size_x / 2;
    $rect_size_x = ($size_x -  $rect_offset * ($count - 1)) / $count;
    if ($rect_size_x > $rect_max_size_x)
        $rect_size_x = $rect_max_size_x;
    
    $rect_max_size_y = $size_y - 100;
    
    $max_count = 0;
    foreach ($diagram_data as $data)
        $max_count = $data[1] > $max_count ? $data[1] : $max_count;
    
    $data_color = imagecolorallocate($im, 49, 106, 236);
    
    $currentX = 10;
    foreach ($diagram_data as $data) {
    
        $title = $data[0];
        $count = $data[1];
    
        drawСolumn($im, $data_color, $currentX, $size_y - $axis_offset_y  + 20, 
        $title, $count, $rect_size_x, $rect_max_size_y * ($count / $max_count));
    
        $currentX += $rect_size_x + $rect_offset ;
    }
}

function drawСolumn($im, $color, $x, $y, $data_name, $data_count, $size_x, $size_y) {

    imagestring($im, 3, $x, $y, $data_name, $color);
    $offset = 20;
    $rectX = $x;
    $rectY = $y - $offset;
    imagefilledrectangle($im, $rectX, $rectY , $rectX + $size_x,  $rectY - $size_y, $color);
    imagestring($im, 3, $rectX, $rectY - $size_y - $offset, $data_count, $color);
}