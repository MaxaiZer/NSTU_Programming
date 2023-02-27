<?php

function echoSelectFromArray($select_name, array $idAndValue, $selected_value = "") {

    echo "<select name=".$select_name.">";

    foreach ($idAndValue as $row) {

        $id = $row[0];
        $value = $row[1];

        $selected = ($value == $selected_value && !empty($selected_value) ? 
        "selected" : "");

        echo "<option value=".$id." ".$selected.">".$value;
    }

    echo "</select>"; 
}

function stringByKeyOrEmpty(array $arr, $key) {
    return isset($arr[$key]) ? $arr[$key] : ""; 
}