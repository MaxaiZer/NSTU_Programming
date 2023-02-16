<?php

$name = $_POST['name'];
$sites = $_POST['sites'];

if (isset($name) && isset($sites)) {
    $date = date("d.m.Y");
    writeToFile("file.txt", $date, " ".$name." ".$sites);
    header("Location: output_file.php"); 
}

function writeToFile($fileName, $date, $data) {

    $fp = fopen($fileName, "a");
    if (!$fp)
    {
        echo "Error open ".$fileName."!";
        exit;
    }

    flock($fp, 2); 

    fwrite($fp, $date."\t".$data."\n");

    flock($fp, 3);
    fclose($fp);
}