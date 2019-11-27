const defaultPrivateKey = "5KZPmRaQq7iqfKWzQTki1d1cdFCbRA7n33NpFc8xvQ47QHpckZL"; // VERY BAD!!!

const eosjsRpcInitialized = new eosjs_jsonrpc.JsonRpc('https://api.jungle.alohaeos.com');

const signatureProvider = new eosjs_jssig.JsSignatureProvider([defaultPrivateKey]);
const eosjsApiInitialized = new eosjs_api.Api({ rpc: eosjsRpcInitialized, signatureProvider: signatureProvider });

let eosiojs = {};

const CONTRACT_ACCOUNT = "hello5world1";
const CALLING_ACCOUNT = "hello5world1"
