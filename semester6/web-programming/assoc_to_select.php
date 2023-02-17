<?php

function echoSelectFromAssocArray(array $arr, array $selected_values) {

    $keys = array_keys($arr[0]);
    $columnName = $keys[0];
 
    $selectedValue = stringByKeyOrEmpty($selected_values, $columnName);
  
    echo "<select name=".$columnName.">";

    foreach ($arr as $row) {
        foreach ($row as $value) {
            $selected = ($value == $selectedValue && !empty($selectedValue) ? 
            "selected" : "");

            echo "<option value=".$value." ".$selected.">".$value;
        }
    }

    echo "</select>"; 
}

function stringByKeyOrEmpty(array $arr, $key) {
    return isset($arr[$key]) ? $arr[$key] : ""; 
}