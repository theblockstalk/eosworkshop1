const defaultPrivateKey = "5KZPmRaQq7iqfKWzQTki1d1cdFCbRA7n33NpFc8xvQ47QHpckZL"; // VERY BAD!!!

const eosjsRpcInitialized = new eosjs_jsonrpc.JsonRpc('https://api.jungle.alohaeos.com');

const signatureProvider = new eosjs_jssig.JsSignatureProvider([defaultPrivateKey]);
const eosjsApiInitialized = new eosjs_api.Api({ rpc: eosjsRpcInitialized, signatureProvider: signatureProvider });

let eosiojs = {};

const CONTRACT_ACCOUNT = "hello5world1";
const CALLING_ACCOUNT = "hello5world1"

eosiojs.get_account = async function (accountName) {
    return await eosjsRpcInitialized.get_account(accountName);
}

eosiojs.contract_transact = async function (action, data) {
    try {
        console.log(eosjsApiInitialized);
        console.log(await eosiojs.get_account(CALLING_ACCOUNT))
        const result = await eosjsApiInitialized.transact({
        actions: [{
            account: CONTRACT_ACCOUNT,
            name: action,
            authorization: [{
                actor: CALLING_ACCOUNT,
                permission: 'active',
            }],
            data: data,
        }]
        }, {
        blocksBehind: 3,
        expireSeconds: 30,
        });
        return result;
        // pre.textContent += '\n\nTransaction pushed!\n\n' + JSON.stringify(result, null, 2);
    } catch (e) {
        console.error(e);
        // pre.textContent = '\nCaught exception: ' + e;
        // if (e instanceof eosjs_jsonrpc.RpcError)
        // pre.textContent += '\n\n' + JSON.stringify(e.json, null, 2);
    }
}