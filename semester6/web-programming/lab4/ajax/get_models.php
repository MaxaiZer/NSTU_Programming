<?php

if($_SERVER["HTTP_X_REQUESTED_WITH"] != "XMLHttpRequest") die();

/*echo "<?xml version='1.0' encoding='UTF-8' standalone='yes'?>";
 */

$brand_id = $_GET["brand_id"];
if (!isset($brand_id)) die();

include_once("../../connect_to_db.php");

$query = "SELECT id, name 
from car_models 
where brand_id = ".$brand_id;

try {  
    $result = $conn->query($query, MYSQLI_USE_RESULT);
} catch (Exception $e) {
    die('Error: ' . $e->getMessage());
}

$dom = new DOMDocument();

$response = $dom->createElement('response');
$dom->appendChild($response);

$models = $dom->createElement('models');
$response->appendChild($models);

while ($row = $result->fetch_assoc()) {
    addToDom($dom, $models, $row["id"], $row["name"]);
}

header("Content-type: text/xml; charset=UTF-8");
echo $dom->saveXML();

function addToDom(DOMDocument &$dom, &$modelsElement, $id, $model_name) {

    $model = $dom->createElement('model');

    $id_elem = $dom->createElement('id');
    $id_elem->appendChild($dom->createTextNode($id));
    $model->appendChild($id_elem);
    
    $name = $dom->createElement('name');
    $name->appendChild($dom->createTextNode($model_name));
    $model->appendChild($name);

    $modelsElement->appendChild($model);
}