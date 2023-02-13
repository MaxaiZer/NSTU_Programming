<?php
header("Location: index.php"); 

$email = $_POST['email'];

$name = $_POST['name'];
$sites = $_POST['sites'];

if (isset($email))
{
	setUserCookie("email", $email);
}

if (isset($name) && isset($sites))
{
    $date = date("d.m.Y");
    writeToFile("file.txt", $date, "name:".$name." sites:".$sites);
}

function setUserCookie($cookieName, $data)
{
    setcookie($cookieName,$data, time()+365*24*60*60);
}    

function writeToFile($fileName, $date, $data)
{
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