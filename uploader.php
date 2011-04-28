<?php
$upload_directory = '/var/www/html/files/';



// In PHP versions earlier than 4.1.0, $HTTP_POST_FILES should be used instead
// of $_FILES.

$id = 0;
if(isset($_REQUEST['id'])) { $id = $_REQUEST['id']; }

if($id != 0)
{

  $uploaddir = $upload_directory . $id . '/';
  if(!file_exists($uploaddir))
  {
    echo "directory ".$uploaddir." doesn't exist, creating... ";
    if(mkdir($uploaddir)) { echo "directory created.<br> \n"; chmod($uploaddir,0777); }
    else { echo "error creating directory.<br \n"; }
  }
  else
  {
    echo "directory already exists, moving on...<br>\n";
  }
  $uploadfile = $uploaddir . basename($_FILES['userfile']['name']);

  if (move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile)) {
      echo $uploadfile." is valid, and was successfully uploaded.<br>\n";
  } else {
      echo "Possible file upload attack on ".$uploadfile."<br>\n";
  }
  chmod($uploadfile,0777);
  echo "uploaded file to ".$uploaddir."<br>\n";
  print "<pre>\n";
  print_r($_FILES);
  print "\n</pre>";
}
else
{
  echo "No id specified<br>\n";
}



?>
