const defaultPrivateKey = "5JtUScZK2XEp3g9gh7F8bwtPTRAkASmNrrftmx4AxDKD5K4zDnr"; // bob
const eosjsRpcInitialized = new eosjs_jsonrpc.JsonRpc('https://api.jungle.alohaeos.com');

const signatureProvider = new eosjs_jssig.JsSignatureProvider([defaultPrivateKey]);
const eosjsApiInitialized = new eosjs_api.Api({ eosjsRpcInitialized, signatureProvider });

let eosiojs = {};

eosiojs.get_account = async function (accountName) {
    return await eosjsRpcInitialized.get_account(accountName);
}