<?php

include("includes/config.php");

$nfcuid = $_POST["wlUID"];
$readerid = $_POST["wlReaderId"];


	global $conn;
    $stmt = $conn->prepare("INSERT INTO whitelist (UID,ReaderID) VALUES (?,?)");
    $stmt->bind_param("si",$nfcuid,$readerid);

    if ($stmt->execute()) {

        echo "ok";

    } else {
        echo "error: " . $stmt->error;
	}

?>