async function onload() {
    updateTable();
    $("#user-alert").hide();
    stringTosha256();
}

async function hiverifyTx() {
    $("#user-alert").show();
    $("#user-alert").html("theatheahte")
}

async function hiTx() {
    const message_hash = $("#message_hash").val();
    await eosiojs.contract_transact("hi", {
        from: CALLING_ACCOUNT,
        message_hash: message_hash
    })
    updateTable();
}

async function updateTable() {
    const tableRows = await eosiojs.get_table_rows();
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