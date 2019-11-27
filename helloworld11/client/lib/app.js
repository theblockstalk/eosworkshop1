async function onload() {
    console.log("web page loading...");
    stringTosha256();
}

async function pause(ms) {
    return new Promise(resolve=>{
        setTimeout(resolve,ms)
    })
}

async function hiTx() {
    console.log("getting account");
    const message_hash = $("#message_hash").val();
    const tx = await eosiojs.contract_transact("hi", {
        from: CALLING_ACCOUNT,
        message_hash: message_hash
    })
    console.log(tx);
}

async function stringTosha256() {
    const text = $("#string").val();
    const hash = await sha256(text);
    $("#hashOfString").val(hash);
    // $("#hashOfString").attr("placeholder", hash);
}