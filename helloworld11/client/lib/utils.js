function displaySuccess(message) {
    $("#user-alert").addClass('alert-success').removeClass('alert-warning')
    $("#user-alert").show();
    $("#user-alert").html(message);    
}

function displayError(message) {
    console.error(message);
    $("#user-alert").addClass('alert-warning').removeClass('alert-success')
    $("#user-alert").show();
    $("#user-alert").html(message);    
}