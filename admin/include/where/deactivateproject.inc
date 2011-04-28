<?php
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	//include('../lib/vulab.projects.class.php');
	include('../include_all.php');
	if ($_POST['deactivating'] == 'yeahimdoingit') {
		$project = new Project;
		$pid = $_POST[pid];
		if (is_numeric($pid) AND $pid > 0) {
			$project->init($pid);
			$data = array('status'=>'3');
			$editresult = $project->update($data);
			if (is_array($editresult)) {
				$errors = $editresult;
			} else {
			
				$onload = ' onLoad="self.parent.window.location=\'manage.php?success=deactivatedproject\';setTimeout(self.parent.tb_remove(),6000);" ';
			}
			
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
		echo "<h1><center>Success!<br/>You have deactivated this project</center></h1>";
	}

} else { ?>
<form action="/admin/manage.php?where=deactivateproject&lay=ajax&id=<?php echo($_GET[id]);?>" method="post">
<h2><center>You are deactivating your project!</center></h2>
<p>This will close your project to testers and will set your project as "completed"</p
<input type="hidden" name="pid" value="<?php echo($_GET[id]);?>" />
<input type="hidden" name="deactivating" value="yeahimdoingit" />
<input type="submit" value="Yes, Deactivate This Project!" />
<input type="button" value="Cancel" onClick="self.parent.tb_remove();"/>
</form>
<?php }  ?>
</center>
</div>
</body>
</html>