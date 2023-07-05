<?php
// Connect to your database
$servername = "your_servername";
$username = "your_username";
$password = "your_password";
$dbname = "your_database";

$uid = $_GET['id'];

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

//Need to add incremental user addition ******************
$stmt = $conn->prepare("INSERT INTO Users/UID VALUES ?");
$stmt->bind_param("ss", $uid);

if ($stmt->execute() === TRUE) {
    $response = "New row added successfully";
} else {
    $response = "Error: " . $stmt->error;
}

$stmt->close();
$conn->close();

// Send the response
echo $response;
?>
