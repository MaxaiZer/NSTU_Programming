<?php

$name = $_POST['name'];
$isExpelled = $_POST['isExpelled'];

if (!isset($name))
{
	echo 'Дурачок, ты имя не ввёл';
    return;
}

setcookie("name",$name,time()+365*24*60*60);
header("location:lab1.php");

$date = date("d.m.Y");
writeToFile("form1.txt", $date, $name);


if ($isExpelled)
    echo 'Вы отчислены, '.$name.'!';
else
    echo 'Пострадайте ещё чуть-чуть, '.$name.'!';


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

function readFromFile($fileName)
{
    $fp = fopen($fileName, "r");
    if (!$fp)
    {
        echo "Error open ".$fileName."!";
        exit;
    }

    flock($fp, 1);

    while(!feof($fp))
    {
        $str = fgets($fp, 100);
        echo $str;
    }


    flock($fp, 3);
    fclose($fp);
}

