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
        const txId = result.transaction_id;
        const url = "https://eosauthority.com/transaction/" + txId + "?network=jungle";
        const alertHtml = "Success. See transaction <a href='"+url+"'>here</a>";
        $("#user-alert").addClass('alert-success').removeClass('alert-warning')
        $("#user-alert").show();
        $("#user-alert").html(alertHtml);    
        return result;
    } catch (e) {
        let message = 'Caught exception: ' + e;
        if (e instanceof eosjs_jsonrpc.RpcError)
        message += '\n\n' + JSON.stringify(e.json, null, 2);
        $("#user-alert").addClass('alert-warning').removeClass('alert-success')
        $("#user-alert").show();
        $("#user-alert").html(message);    
        console.error(e);
    }
}

eosiojs.get_table_rows = async function () {
    const args = {
        code: CONTRACT_ACCOUNT,
        table: "messages",
        scope: CONTRACT_ACCOUNT,
        lower_bound: CALLING_ACCOUNT
    }
    return await eosjsRpcInitialized.get_table_rows(args);
}