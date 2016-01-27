$(document).ready(function() {
  // Add the page method call as an onclick handler for the div.
  $("#go").click(function() {
    $.ajax({
      type: "POST",
      url: "Default.aspx/Button4Click",
      data: "{}",
      contentType: "application/json; charset=utf-8",
      dataType: "json",
      success: function(msg) {
        // Replace the div's content with the page method's return.
        $("#Result").text(msg.d);
      }
    });
  });
});

