<?php
$servername = "rfidatabase";
$username = "id20912123_rfidbase";
$password = "Secure@123";
$dbname = "id20912123_myrfid";

$value = $_GET['uid'];
$resp = "";

$conn = new mysqli($servername, $username, $password, $dbname);

// Check the connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT UID FROM Users/UID WHERE UID = '$uid'";
$result = $conn->query($sql);

// Check if the query returned any rows
if ($result->num_rows > 0) {
    $resp = "Valid";
} else {
    $resp = "Invalid";
}


$conn->close();

echo $resp;
?>