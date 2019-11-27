async function onload() {
    $("#user-alert").hide();
    await login();
    updateTable();
    stringTosha256();
}

async function hiverifyTx() {
}

async function hiTx() {
    const message_hash = $("#message_hash").val();
    await walletContract.hi(message_hash);
    updateTable();
}

async function updateTable() {
    const tableRows = await walletContract.getMessages();
    const row = tableRows.rows[0];
    
    $("#user-account").html(row.user);
    $("#user-hash").html(row.hash);
    $("#user-updated").html(row.last_updated);
}

async function stringTosha256() {
    const text = $("#string").val();
    const hash = await sha256(text);
    $("#hashOfString").val(hash);
}