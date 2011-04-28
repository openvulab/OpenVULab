<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?>
<?php
	//error_reporting(E_ALL);
	//ini_set('display_errors', '1');
/* $Id: head.inc,v 1.9 2005/04/14 17:51:16 greggmc Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */
$base = $CONFIG['url']['base'].$_SERVER['PHP_SELF'];
?>
<div id="main">
  <div id="header">
  
<!--	
<div align="center"><a href="?where=manage"><img style="margin:10px;" src="<?php echo($CONFIG['url']['logo']); ?>" /></a><br/><strong/><?php echo $SITE['slogan']; ?></strong></div>
-->

<div style="width: 100%; text-align: center">
<div style="margin: auto;">

<div class="usergreeting" style="text-align:right;">
<h3 class="right pad" style="padding-right:0px;"><?php echo ('Welcome '. $_SESSION['acl']['username']); ?> </h3>
<div class="clear"></div>
&nbsp;&nbsp;
<a href="<?php echo("${base}?where=manage");  ?>"><?php echo(_('Home')); ?></a>
<?php /*&nbsp;&nbsp;
<a href="<?php echo("${base}?where=account");  ?>"><?php echo(_('My Account')); ?></a>*/ ?>
&nbsp;&nbsp;
<a href="http://vimeo.com/2732747" class="new_window"><?php echo(_('VULab Help')); ?></a>
&nbsp;&nbsp;
<a href="<?php echo("${base}?where=help");  ?>"><?php echo(_('Survey Help')); ?></a>
	<?php if($GLOBALS['ESPCONFIG']['auth_design']) { ?>
			&nbsp;&nbsp;
			        
                           <a href="<?php echo("${base}?where=logout");  ?>"><?php echo(_('Sign Out')); ?></a>
   
    <?php } ?>
    
<?php if ($_SESSION['acl']['superuser'] == 'Y') { ?>
	<?php /*if ($_SESSION[acl]['superuser'] == 'Y') { */?>
	<?php if (!$_SESSION[debug]) { ?>
	&nbsp;&nbsp;
	<a href="<?php echo("${base}?debug=true");  ?>"><?php echo(_('Turn on Debugging')); ?></a>
	<?php } else {?>	
	&nbsp;&nbsp;
	<a href="<?php echo("${base}?debug=off");  ?>"><?php echo(_('Turn off Debugging')); ?></a>
	<?php } ?>	
<?php } ?>
<?php /*<br />
Something Broken? Bug? Check The <a href="http://wiki.fluidproject.org/display/fluid/VULab+WEB+-+Live+Development+Status" target="_blank"><?php echo(_('Development Status')); ?></a>*/ 
?>
</div>
</div>
</div>


	
  
  </div> <!-- end header div -->
  
  <div id="body">
      <div class="contents">
      <br/>
      <form method="post" id="containerform" action="<?php echo($base); ?>" onsubmit="isSubmit()">