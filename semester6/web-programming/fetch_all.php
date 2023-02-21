<?php

function fetch_all(mysqli_result $result, $mode) { //because fetch_all() not supported on the server lmao (php 5.3.3)

    $rows = array();
    while ($row = $result->fetch_array($mode))
        $rows[]=$row;

    return $rows;
}