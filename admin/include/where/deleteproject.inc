<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	include('../lib/vulab.projects.class.php');
	if ($_POST['deleting'] == 'yeahimdoingit') {
		$project = new Project;
		$pid = $_POST[pid];
		if (is_numeric($pid) AND $pid > 0) {
			$project->init($pid);
			$deleteresult = $project->delete();
			if (is_array($deleteresult)) {
				$errors = $deleteresult;
			} else {
			
				$onload = ' onLoad="self.parent.window.location=\'/admin/manage.php?success=deletedproject\';setTimeout(self.parent.tb_remove(),6000);" ';
			}
			
		}
	}
}
?>
<html>
<head>
<link href="/admin/style.css" rel="stylesheet" type="text/css" />
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
		echo "<h1><center>Success!<br/>You have deleted this project</center></h1>";
	}

} else { ?>
<form action="/admin/manage.php?where=deleteproject&lay=ajax&id=<?php echo($_GET[id]);?>" method="post">
<h2><center>Your project will be deleted, forever!</center></h2>
<?php
/*<div>yes <input type="radio" name="keepsurvey" vaue="true"/> no <input type="radio" name="keepsurvey" value="false"/></div>*/
?>
<div><strong>deleting this project will not delete any surveys in other projects</strong></div>
<br /><br/>
<input type="hidden" name="pid" value="<?php echo($_GET[id]);?>" />
<input type="hidden" name="deleting" value="yeahimdoingit" />
<input type="submit" value="Yes, Delete This Project!" />
<input type="button" value="Cancel" onClick="self.parent.tb_remove();"/>
</form>
<?php }  ?>
</center>
</div>
</body>
</html>
