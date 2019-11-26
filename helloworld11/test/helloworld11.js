const assert = require('assert');
const eoslime = require('eoslime').init('local');
let eos;
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
        /*
            `deploy` creates for you a new account behind the scene
            on which the contract code is deployed

            You can access the contract account as -> contractAccount.executor
        */
        contractAccount = await eoslime.Contract.deploy(CONTRACT_WASM_PATH, CONTRACT_ABI_PATH);
        eos = contractAccount.provider.eos;
    });

    it('Should create a new token', async () => {
        let tx = await contractAccount.hi(myAccount.name, "hello world");

        

        /*
            You have access to the EOS(eosjs) instance:
                eoslime.Provider.eos
        */
        let tokenInitialization = await eos.getCurrencyStats(contractAccount.name, 'SYS');

        assert.equal(tokenInitialization.SYS.max_supply, TOTAL_SUPPLY, 'Incorrect tokens supply');
        assert.equal(tokenInitialization.SYS.issuer, myAccount.name, 'Incorrect tokens issuer');
    });

    // it('Should issue tokens', async () => {
    //     await contractAccount.create(myAccount.name, TOTAL_SUPPLY);
    //     await contractAccount.issue(tokensHolder.name, HOLDER_SUPPLY, 'memo', { from: myAccount });

    //     let holderBalance = await tokensHolder.getBalance('SYS', contractAccount.name);
    //     assert.equal(holderBalance[0], HOLDER_SUPPLY, 'Incorrect holder balance');
    // });

    // it('Should throw if tokens quantity is negative', async () => {
    //     await contractAccount.create(myAccount.name, TOTAL_SUPPLY);
    //     const INVALID_ISSUING_AMOUNT = '-100.0000 SYS';

    //     /*
    //         eoslime provides you testing utils (Available only if testing with `eoslime test`)
    //     */
    //     await eoslime.tests.expectAssert(
    //         contractAccount.issue(tokensHolder.name, INVALID_ISSUING_AMOUNT, 'memo', { from: myAccount })
    //     );

    //     let holderBalance = await tokensHolder.getBalance('SYS', contractAccount.name);
    //     assert.equal(holderBalance.length, 0, 'Incorrect holder balance');
    // });
});