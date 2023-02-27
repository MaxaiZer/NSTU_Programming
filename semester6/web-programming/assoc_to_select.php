<?php

function echoSelectFromArray($select_name, array $value_and_label, $selected_label = "") {

    echo "<select name=".$select_name.">";

    foreach ($value_and_label as $row) {

        $value = $row[0];
        $label = $row[1];

        $selected = ($label == $selected_label && !empty($selected_label) ? 
        "selected" : "");

        echo "<option value=".$value." ".$selected.">".$label;
    }

    echo "</select>"; 
}

function stringByKeyOrEmpty(array $arr, $key) {
    return isset($arr[$key]) ? $arr[$key] : ""; 
}