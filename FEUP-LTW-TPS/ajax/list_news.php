<?php
  include_once('database/connection.php');
  include_once('database/news.php');

  $articles = getAllNews();

  include_once('templates/common/header.php');
  include_once('templates/news/list_news.php');
  include_once('templates/common/footer.php');
?>
