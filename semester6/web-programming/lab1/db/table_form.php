<?php

if (!isset($conn))
    die ("Connection valiable 'conn' doesn't set from calling script");

$selected_values = array();

if (isset($id)) {  
    $query = "SELECT car_brands.name as brand, 
    license_plate_number as number, state, car_owners.surname as surname
    FROM cars
    inner join car_brands on car_brands.id = brand_id
    inner join car_owners on car_owners.id = owner_id where cars.id=".$id;

    $result = $conn->query($query, MYSQLI_USE_RESULT);
    $selected_values = $result->fetch_array(MYSQLI_ASSOC);
    
    $result->free();
}

echoInputForm($conn, $selected_values);

function echoInputForm($conn, $selected_values){
    
    $query = "SELECT car_owners.surname FROM car_owners";
    $owners = $conn->query($query, MYSQLI_USE_RESULT);
    $iter = $owners->getIterator();
    
    echo "Surname";
    echoSelectFromRows("surname", $iter, "surname", $selected_values["surname"]);
    
    $owners->free();
    
    $query = "SELECT car_brands.name as brand FROM car_brands";
    $brands = $conn->query($query, MYSQLI_USE_RESULT);
    $iter = $brands->getIterator();
    
    echo "Brand";
    echoSelectFromRows("brand", $iter, "brand", $selected_values["brand"]);
    
    $brands->free();
    
    echo "Car number <input type='text' name = 'number' value=".$selected_values["number"].">";
    
    $states = array("stolen", "found");
    echoSelect("state", $states, $selected_values["state"]);
}

function echoSelectFromRows($selectName, $rowsIter, $columnName, $selectedValue = "") {

    echo "<select name=".$selectName.">";

    while ($rowsIter->valid()) {
        $row = $rowsIter->current();  
        $data = $row[$columnName];

        $selected = ($data == $selectedValue && !empty($selectedValue) ? 
        "selected" : "");

        echo "<option value=".$data." ".$selected.">".$data;
    
        $rowsIter->next();
    }

    echo "</select>"; 
}

function echoSelect($selectName, array $values, $selectedValue = "") {

    echo "<select name=".$selectName.">";

    $iter = (new ArrayObject($values))->getIterator();

    while ($iter->valid()) {
        $data = $iter->current();

        $selected = ($data == $selectedValue && !empty($selectedValue) ? 
        "selected" : "");

        echo "<option value=".$data." ".$selected.">".$data;
    
        $iter->next();
    }

    echo "</select>"; 
}
