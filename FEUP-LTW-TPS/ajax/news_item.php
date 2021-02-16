<?php
  include_once('database/connection.php');
  include_once('database/news.php');
  include_once('database/comments.php');
  
  if (!isset($_GET['id']))
    die("No id!");

  $article = getNewsById($_GET['id']);
  $paragraphs = explode("\n", $article['fulltext']);
  $comments = getCommentsByNewId($_GET['id']);

  include('templates/common/header.php');
  include('templates/news/news_item.php');
  include('templates/common/footer.php');
?>
