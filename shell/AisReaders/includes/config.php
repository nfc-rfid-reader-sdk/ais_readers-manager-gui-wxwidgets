<?php
$servername="localhost";
$username="root";
$password="";
$database="Logs";
$conn=new mysqli($servername,$username,$password,$database);
mysqli_set_charset($conn,"utf8");

if ($conn->connect_error) {
    die("konekcija nije uspela: " .$conn_>connect_error);
}
?>