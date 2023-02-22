<?php
session_start(); 

if (!isset($_SESSION['captcha_keystring']) ||
    !isset($_POST['captcha_answer']))
    die();
   
if ($_SESSION['captcha_keystring'] != $_POST['captcha_answer']) {   

    $_SESSION["is_right_captcha"] = false;
    header("Location: index.php");
    die();
}

$_SESSION["is_right_captcha"] = true;   

$text = $_POST['text'];

if (isset($text)) {
    $date = date("d.m.Y");
    writeToFile("file.txt", $date, " ".$text);
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