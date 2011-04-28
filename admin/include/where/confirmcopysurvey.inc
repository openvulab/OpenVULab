<?php
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	//include('../lib/vulab.projects.class.php');
	//include('include_all.php');
	//include('include/function/survey_copy.inc');
	if ($_POST['confirmcopy'] == 'yeahimdoingit') {
		$pid = $_GET['pid'];
		$sid = $_GET['sid'];
		$newsid = survey_copy($sid);
		
		if ($newsid > 0) {
			$onload = ' onLoad="self.parent.window.location=\'manage.php?where=survey_tool&pid='.$pid.'&lay=form&newid='.$newsid.'\';setTimeout(self.parent.tb_remove(),6000);" ';
		} else {
			$errors = array("Unable to copy survey, please try again");
		}
	}
}
?>
<html>
<head>
<link href="style.css" rel="stylesheet" type="text/css" />
</head>
<body <?php echo($onload);?>>
<div class="padded">
<br/>
<center>
<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') { 
	if ($errors) { 
		echo "<div class='errors'>";
		foreach ($errors as $error) {
			echo $error;
		}
		echo "</div>";
	} else {
		echo "<h1><center>Success!<br/>You copied this survey</center></h1>";
	}

} else { ?>
<form action="/admin/manage.php?where=confirmcopysurvey&lay=ajax&pid=<?php echo($_GET['pid']);?>&sid=<?php echo($_GET['sid']);?>" method="post">
<h2><center>Use this Survey?</center></h2>
<p>This will copy everything from existing survey, which you can then edit</p>
<input type="hidden" name="pid" value="<?php echo($_GET[pid]);?>" />
<input type="hidden" name="confirmcopy" value="yeahimdoingit" />
<input type="submit" value="Yes, use this survey" />
<input type="button" value="Cancel" onClick="self.parent.tb_remove();"/>
</form>
<?php }  ?>
</center>
</div>
</body>
</html>