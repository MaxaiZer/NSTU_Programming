<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL & ~E_NOTICE  & ~E_WARNING);

try {
    $conn = new mysqli("localhost", "root", "12345");
} catch (Exception $e) {
    die ($e->getMessage());
}

$db_name = "stolen_cars";
mysqli_select_db($conn, $db_name) or die (mysqli_error($conn));