<?php

include_once('connection.php');

function getComments(){
    global $db;
    $stmt = $db->prepare("SELECT * FROM users JOIN comments USING (username) WHERE news_id= ?");
    $stmt->execute(array($_GET['id']));
    $comments = $stmt->fetchAll();
    return $comments;
}

?>
