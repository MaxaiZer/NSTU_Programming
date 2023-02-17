<?php
header("Location: index.php");

$email = $_POST['email'];
$date=date("d.m.Y");

if (isset($email)) {
    setcookie("email",$email, time()+365*24*60*60);
    setcookie("date",$date, time()+365*24*60*60);
}
