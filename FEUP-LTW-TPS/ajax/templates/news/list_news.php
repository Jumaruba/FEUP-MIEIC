<section id="news">
  <?php foreach($articles as $article) { ?>
  <article>
    <header>
      <h1><a href="news_item.php?id=<?=$article['id']?>"><?=$article['title']?></a></h1>
    </header>
    <img src="http://lorempixel.com/600/300/business/" alt="">
    <p><?=$article['introduction']?></p>
    <footer>
      <span class="author"><?=$article['name']?></span>
      <?php $tags = explode(',', $article['tags']); ?>
      <span class="tags">
        <?php foreach ($tags as $tag) { ?>
          <a href="list_news.php?tag=<?=$tag?>">#<?=$tag?></a>
        <?php } ?>
      </span>
      <span class="date"><?=date('Y-m-d H:i:s', $article['published']);?></span>
      <a class="comments" href="news_item.php?id=<?=$article['id']?>#comments"><?=$article['comments']?></a>
    </footer>
  </article>
<?php } ?>
</section>
