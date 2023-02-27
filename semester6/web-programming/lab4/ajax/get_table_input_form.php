<?php
include_once("../../connect_to_db.php");
include_once("../../fetch_all.php");
include_once("../../assoc_to_select.php");

$selected_values = array();

if (isset($id)) {  

    $query = "SELECT car_brands.name as brand, 
    car_models.name as model,
    license_plate_number as number, state, car_owners.surname as surname
    FROM cars_v2
    inner join car_models on car_models.id = model_id
    inner join car_brands on car_brands.id = car_models.brand_id
    inner join car_owners on car_owners.id = owner_id where cars_v2.id=".$id;

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

    $result = $conn->query("SELECT id, surname FROM car_owners", MYSQLI_USE_RESULT);
    echo "Surname";
    echoSelectFromArray("owner_id", fetch_all($result, MYSQLI_NUM), $selected_values["surname"]);
   
    $result = $conn->query("SELECT id, name as brand FROM car_brands", MYSQLI_USE_RESULT);
    echo "Brand";

    $arr = fetch_all($result, MYSQLI_NUM);

    if (!isset($selected_values["brand"])) {
        array_unshift($arr, array(0, ""));
        $selected_values["brand"] = "";
    }
    echoSelectFromArray("brand_id", $arr, $selected_values["brand"]);

    echo "Model";

    if (!empty($selected_values["brand"])) {
        $result = $conn->query("SELECT car_models.id, car_models.name as model 
        FROM car_models 
        inner join car_brands on car_brands.id = brand_id 
        where car_brands.name = '".$selected_values["brand"]."'", MYSQLI_USE_RESULT);

        echoSelectFromArray("model_id", fetch_all($result, MYSQLI_NUM), $selected_values["model"]);
    } else {
        echo "<select name='model_id'></select>";
    }
    
    echo "Car number <input type='text' name = 'number' value=".
    stringByKeyOrEmpty($selected_values, "number").">";
    
    $states = array(array("stolen", "stolen"), array ("found", "found"));
    echoSelectFromArray("state", $states, $selected_values["state"]);
}