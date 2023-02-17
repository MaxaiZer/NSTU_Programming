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

echoInputForm($conn, $selected_values);

function echoInputForm($conn, array $selected_values) {

    echo "Login:";
    $format = "<input type='text' name='%s' value='%s'>";
    echo sprintf($format, "login", $selected_values["login"]);

    echo "Password:";
    $format = "<input type='password' name='%s'>";
    echo sprintf($format, "password");

    echo "Role:";
    $roles = array(array("role" => "moderator"), array ("role" => "admin"));
    echoSelectFromAssocArray($roles, $selected_values);
}