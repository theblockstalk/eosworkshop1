const assert = require('assert');
const eoslime = require('eoslime').init('local');
const eos = eoslime.Provider.eos;
const crypto = require("./crypto");

const CONTRACT_WASM_PATH = './build/helloworld11.wasm';
const CONTRACT_ABI_PATH = './build/helloworld11.abi';

describe('helloworld11', function () {
    // Increase mocha(testing framework) time, otherwise tests fails
    this.timeout(15000);

    let contractAccount;
    let myAccount;

    before(async () => {
        let accounts = await eoslime.Account.createRandoms(1);
        myAccount = accounts[0];
    });

    beforeEach(async () => {
        contractAccount = await eoslime.Contract.deploy(CONTRACT_WASM_PATH, CONTRACT_ABI_PATH);
    });

    it('Should say store the hash', async () => {
        const messagesTable = contractAccount.messages;
        let messages = await messagesTable.limit(10).find();
        
        assert.equal(messages.length, 0, "Should not have any rows yet");
        const messageString = "hello world";
        const message_hash = crypto.sha256(messageString);
        let tx = await contractAccount.hi(myAccount.name, message_hash, {from: myAccount});

        messages = await messagesTable.equal(myAccount.name).find();
        const message = messages[0];
        assert.equal(message.user, myAccount.name, "account name not correct");
        assert.equal(message.hash, message_hash, "hash was not stored in the table");
    });
});