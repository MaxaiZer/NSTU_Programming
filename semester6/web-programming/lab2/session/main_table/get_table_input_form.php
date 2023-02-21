<?php
include_once("../../../connect_to_db.php");
include_once("../../../fetch_all.php");
include_once("../../../assoc_to_select.php");

$selected_values = array();

if (isset($id)) {  

    $query = "SELECT car_brands.name as brand, 
    license_plate_number as number, state, car_owners.surname as surname
    FROM cars
    inner join car_brands on car_brands.id = brand_id
    inner join car_owners on car_owners.id = owner_id where cars.id=".$id;

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

    $result = $conn->query("SELECT car_owners.surname FROM car_owners", MYSQLI_USE_RESULT);
    echo "Surname";
    echoSelectFromAssocArray(fetch_all($result, MYSQLI_ASSOC), $selected_values);
   
    $result = $conn->query("SELECT car_brands.name as brand FROM car_brands", MYSQLI_USE_RESULT);
    echo "Brand";
    echoSelectFromAssocArray(fetch_all($result, MYSQLI_ASSOC), $selected_values);
    
    echo "Car number <input type='text' name = 'number' value=".
    stringByKeyOrEmpty($selected_values, "number").">";
    
    $states = array(array("state" => "stolen"), array ("state" => "found"));
    echoSelectFromAssocArray($states, $selected_values);
}