
<?php
  	require("../includes/config.php");
	
  	if($_SERVER["REQUEST_METHOD"]=="POST")
	{
		$stock = lookup($_POST["code"]);
		if($_POST === false)
		{
			apologize("No stock symbol found");
		}
		else
		{
		 render("quote_result.php", [  "price" => $stock["price"]]);
		}
	}
	else
	{
		render("quote_form.php", ["title" => "Quote"]);
	}
?>
