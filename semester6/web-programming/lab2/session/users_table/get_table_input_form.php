<?php
include_once("../../../connect_to_db.php");
include_once("../../../fetch_all.php");
include_once("../../../assoc_to_select.php");

$selected_values = array();

if (isset($id)) {  
    
    $query = "SELECT id, login, role from users where id=".$id;

    try { 
        $result = $conn->query($query, MYSQLI_USE_RESULT); 
    } catch (Exception $ex){
        die($ex->getMessage());
    }
    $selected_values = $result->fetch_array(MYSQLI_ASSOC); 
    $result->free(); 
}

echoInputForm($selected_values);

function echoInputForm(array $selected_values) {

    echo "<p>Login:</p>";
    $format = "<input type='text' name='%s' value='%s'>";
    echo sprintf($format, "login", $selected_values["login"]);

    echo "<p>Password:</p>";
    $format = "<input type='password' name='%s'>";
    echo sprintf($format, "password");

    echo "<p>Password again:</p>";
    $format = "<input type='password' name='%s'>";
    echo sprintf($format, "password_again");

    echo "<p>Role:</p>";
    $roles = array(array("moderator", "moderator"), array ("admin", "admin"));
    echoSelectFromArray("role", $roles, $selected_values["role"]);
}