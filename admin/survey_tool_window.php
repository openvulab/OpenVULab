<?php
include_once("include_all.php");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title><?php echo($SITE['title']); ?></title>
    <script type="text/javascript" src="<?php echo($CONFIG['url']['js']);?>default.js"></script>
	<script type="text/javascript" src="<?php echo($CONFIG['url']['js']);?>jquery-1.2.6.pack.js"></script>
    <script type="text/javascript" src="<?php echo($CONFIG['url']['js']);?>jquery.ajaxContent.js"></script>
    <script type="text/javascript" src="<?php echo($CONFIG['url']['js']);?>vulab.admin.js"></script>
    <script type="text/javascript" src="<?php echo($CONFIG['url']['js']);?>jquery.form.js"></script>
    <script type="text/javascript" src="<?php echo($CONFIG['url']['js']);?>thickbox.js"></script>
	<script type="text/javascript" src="<?php echo($CONFIG['url']['js']);?>jquery.curvycorners.min.js"></script>
    <link rel="stylesheet" href="<?php echo($CONFIG['url']['js']);?>thickbox.css" type="text/css" media="screen" />
    
<?php
	if(!empty($CONFIG['url']['admin-css'])) {
		echo("<link href=\"". $CONFIG['url']['admin-css'] ."\" rel=\"stylesheet\" type=\"text/css\" />\n");
	}
	if(!empty($ESPCONFIG['charset'])) {
		echo('<meta http-equiv="Content-Type" content="text/html; charset='. $ESPCONFIG['charset'] ."\" />\n");
	}
?>
</head>
<body><div>
    <iframe id="surveytool" style="<?php if ($project->details['pre_source']) echo 'display:block;'; ?>" src="manage.php?where=survey_tool&pid=<?php echo($project->id);?>&lay=form&<?php echo ($project->pre_survey[id]) ? 'newid='.$project->pre_survey[id] : 'new=true'; ?>">
    </iframe>
</div>
</body>
</html>
