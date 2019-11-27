async function onload() {
    console.log("web page loading...");
}

async function pause(ms) {
    return new Promise(resolve=>{
        setTimeout(resolve,ms)
    })
}

async function hiTx() {
    console.log("getting account");
    const account = await eosiojs.get_account("hello5world1");
    console.log(account);
}

async function stringTosha256() {
    const text = $("#string").val();
    const hash = await sha256(text);
    $("#hashOfString").attr("placeholder", hash);
}