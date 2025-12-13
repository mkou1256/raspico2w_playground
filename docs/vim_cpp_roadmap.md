# Vim/Neovim C/C++開発環境構築ロードマップ

## 学習の進め方

- 各フェーズの「クリア条件」を全て達成したら次のフェーズへ進む
- 焦らず、確実に一つずつマスターしていく
- 毎日30分〜1時間の練習を推奨
- 実際のコードを書きながら学ぶことが最重要

---

## 【基礎編】Vimでの開発環境構築

### Phase 1: Vim基本操作のマスター（目安: 1-2週間）

#### このフェーズで得られるもの
**できるようになること:**
- マウスなしでテキスト編集ができる
- カーソル移動が圧倒的に速くなる（矢印キーの10倍速）
- 「コピー→移動→ペースト」が一瞬で完了
- ファイル内の目的の場所に2秒でジャンプできる

**どれくらい楽になるか:**
- 従来: マウスとキーボードを行き来して30秒かかっていた編集作業
- Phase 1後: キーボードだけで5秒で完了
- 手首の疲労が劇的に減少（マウス移動がなくなるため）
- 「あの部分を直したい」と思った瞬間に手が動くようになる

#### 学習内容
1. **vimtutorの完走**
   ```bash
   vimtutor
   ```

2. **基本的なモード切り替え**
   - ノーマルモード（Esc）
   - 挿入モード（i, a, o, O）
   - ビジュアルモード（v, V, Ctrl+v）
   - コマンドラインモード（:）

3. **カーソル移動**
   - 基本移動: h, j, k, l
   - 単語移動: w, b, e
   - 行内移動: 0, ^, $
   - ファイル内移動: gg, G, 行番号+G

4. **基本的な編集操作**
   - 削除: x, dd, dw, D
   - コピー&ペースト: yy, yw, p, P
   - アンドゥ&リドゥ: u, Ctrl+r
   - 検索: /, ?, n, N
   - 置換: :s/old/new/g

5. **ファイル操作**
   - 保存: :w
   - 終了: :q, :q!, :wq
   - 新規ファイル: :e filename

#### クリア条件
- [ ] vimtutorを最後まで完了した
- [ ] マウスを使わずにVimでテキストを編集できる
- [ ] 簡単なC言語プログラム（Hello World）をVimで書いて保存できる
- [ ] ファイル内の特定の文字列を検索・置換できる
- [ ] コピー、削除、ペーストを自然に使える
- [ ] 以下のコマンドを見ずに実行できる: `:w`, `:q`, `dd`, `yy`, `p`, `u`, `gg`, `G`

#### 練習課題
```c
// この課題をVimで入力し、編集練習をする
#include <stdio.h>

int main() {
    printf("Hello, Vim!\n");
    return 0;
}
```
- ファイルを開く → コードを書く → 保存 → コンパイル → 実行の流れを10回繰り返す

---

### Phase 2: 基本的な.vimrc設定（目安: 1週間）

#### このフェーズで得られるもの
**できるようになること:**
- 行番号を見ながら正確にコードをナビゲート
- 括弧の対応が一目で分かる（ネストミスが激減）
- 検索結果がハイライトされて見落としがなくなる
- タブとスペースの問題から解放される
- 2つのファイルを並べて比較・編集できる

**どれくらい楽になるか:**
- 従来: 「あれ、この括弧どこで閉じてる？」と10分探す
- Phase 2後: カーソルを置くだけで対応する括弧がハイライト、3秒で解決
- インデントの手動調整が不要に（自動で整形される）
- シンタックスエラーの発見時間が1/3に短縮
- ウィンドウ分割で「ヘッダーを見ながら実装を書く」が可能に

#### 学習内容
1. **環境準備**
   ```bash
   sudo apt update
   sudo apt install vim build-essential
   ```

2. **.vimrcファイルの作成**
   ```bash
   vim ~/.vimrc
   ```

3. **基本設定の追加**
   ```vim
   " 表示設定
   set number              " 行番号表示
   set relativenumber      " 相対行番号
   set cursorline          " カーソル行をハイライト
   set showmatch           " 対応する括弧をハイライト
   set wildmenu            " コマンドライン補完
   syntax on               " シンタックスハイライト
   
   " 検索設定
   set incsearch           " インクリメンタルサーチ
   set hlsearch            " 検索結果をハイライト
   set ignorecase          " 検索時に大文字小文字を無視
   set smartcase           " 大文字が含まれる場合は区別
   
   " インデント設定
   set tabstop=4           " タブの幅
   set shiftwidth=4        " 自動インデントの幅
   set expandtab           " タブをスペースに変換
   set autoindent          " 自動インデント
   set smartindent         " スマートインデント
   
   " エンコーディング
   set encoding=utf-8
   set fileencoding=utf-8
   ```

4. **ウィンドウ分割の練習**
   - 横分割: `:split` または `:sp`
   - 縦分割: `:vsplit` または `:vsp`
   - 移動: Ctrl+w h/j/k/l

#### クリア条件
- [ ] `~/.vimrc`ファイルを作成し、基本設定を記述した
- [ ] Vimを再起動して設定が反映されることを確認した
- [ ] 行番号、シンタックスハイライトが表示されている
- [ ] タブキーを押すとスペース4つに変換される
- [ ] ウィンドウを分割して、複数ファイルを同時に開ける
- [ ] `:set number?`で設定値を確認できる

#### 練習課題
- `.vimrc`に設定を1行追加 → Vimを再起動 → 動作確認、を5回繰り返す
- ウィンドウを分割して、.cファイルと.hファイルを同時に編集する

---

### Phase 3: プラグインマネージャーの導入（目安: 2-3日）

#### このフェーズで得られるもの
**できるようになること:**
- ファイルツリーで視覚的にプロジェクト構造を把握
- ワンキーでファイルツリーの表示/非表示切り替え
- 現在のファイル名や編集モードが常に表示される
- 見やすいカラースキームで目の疲れが軽減
- 新しい機能を簡単に追加できる拡張性を獲得

**どれくらい楽になるか:**
- 従来: `:e src/utils/helper.c`のようにパスを覚えて入力
- Phase 3後: Ctrl+nでツリー表示、矢印キーで選択、Enterで開く
- プロジェクトの全体像が視覚的に把握できる（迷子にならない）
- ステータスラインで「今どのモードか」が一目瞭然
- 1時間コーディングしても目が疲れにくいカラースキーム

#### 学習内容
1. **vim-plugのインストール**
   ```bash
   curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
   ```

2. **.vimrcにプラグインセクションを追加**
   ```vim
   " プラグイン設定の開始
   call plug#begin('~/.vim/plugged')
   
   " ファイルツリー
   Plug 'preservim/nerdtree'
   
   " ステータスライン
   Plug 'vim-airline/vim-airline'
   Plug 'vim-airline/vim-airline-themes'
   
   " カラースキーム
   Plug 'morhetz/gruvbox'
   
   call plug#end()
   
   " カラースキーム設定
   colorscheme gruvbox
   set background=dark
   
   " NERDTreeのキーマッピング
   nnoremap <C-n> :NERDTreeToggle<CR>
   ```

3. **プラグインのインストール**
   - Vimを開く
   - `:PlugInstall`を実行
   - インストール完了を待つ

4. **基本的なキーマッピングの理解**
   ```vim
   " リーダーキーの設定
   let mapleader = " "
   
   " NERDTreeトグル
   nnoremap <leader>n :NERDTreeToggle<CR>
   ```

#### クリア条件
- [ ] vim-plugが正常にインストールされた
- [ ] `:PlugInstall`でプラグインをインストールできた
- [ ] NERDTreeが起動する（Ctrl+nで表示/非表示切り替え）
- [ ] vim-airlineがステータスラインに表示されている
- [ ] カラースキーム（gruvbox）が適用されている
- [ ] プラグインの追加・削除・更新の方法を理解した

#### 練習課題
- NERDTreeを使ってファイルを開く練習を10回
- 新しいプラグインを1つ追加してみる（例: vim-commentary）

---

### Phase 4: Neovimへの早期移行（目安: 2-3日）

#### このフェーズで得られるもの
**できるようになること:**
- VimからNeovimへスムーズに移行
- 既存の設定をそのまま利用
- より高速な動作環境を獲得
- 最新のLSP機能にアクセス可能に
- coc.nvimの問題を回避

**どれくらい楽になるか:**
- 従来（Vim）: coc.nvimが古いVimバージョンで動作しない
- Phase 4後: Neovimのネイティブ機能で問題解決
- プラグインの互換性問題から解放
- より安定した開発環境を獲得
- **この移行により、Phase 5以降がよりスムーズに**

#### 学習内容

1. **Neovimのインストール**
   ```bash
   # Ubuntu 22.04の場合
   sudo apt install neovim
   
   # 最新版が欲しい場合（推奨）
   sudo add-apt-repository ppa:neovim-ppa/unstable
   sudo apt update
   sudo apt install neovim
   
   # バージョン確認
   nvim --version
   ```

2. **既存のVim設定を移行**
   ```bash
   # Neovimの設定ディレクトリを作成
   mkdir -p ~/.config/nvim
   
   # VimのプラグインディレクトリもNeovimで使う
   # （vim-plugは両方で共有可能）
   
   # 既存の.vimrcをNeovimで使う（互換モード）
   ln -s ~/.vimrc ~/.config/nvim/init.vim
   ```

3. **Neovimの起動と動作確認**
   ```bash
   # Neovimを起動
   nvim
   
   # Vim内で健全性チェック
   :checkhealth
   ```

4. **既存プラグインの動作確認**
   ```vim
   " Neovim内で実行
   :PlugInstall
   :PlugUpdate
   
   " NERDTreeが動くか確認
   :NERDTreeToggle
   
   " vim-airlineが表示されているか確認
   ```

5. **エイリアスの設定（オプション）**
   ```bash
   # ~/.bashrcまたは~/.zshrcに追加
   alias vim='nvim'
   alias vi='nvim'
   
   # 反映
   source ~/.bashrc  # または source ~/.zshrc
   ```

#### クリア条件
- [ ] Neovimがインストールされた
- [ ] `nvim`コマンドで起動できる
- [ ] `:checkhealth`を実行してエラーがない（警告は無視してOK）
- [ ] 既存のプラグイン（NERDTree、vim-airline）が正常に動作する
- [ ] Phase 1-3で学んだ操作が全て同じように使える
- [ ] C言語のファイルを開いてシンタックスハイライトが表示される

#### 練習課題
- Neovimで以前作成したC言語ファイルを開く
- 編集してみて、Vimと同じように使えることを確認
- `:checkhealth`の結果を読んで、環境の状態を把握する

---

### Phase 5: C/C++開発の基礎環境（Neovim版）（目安: 1週間）

#### このフェーズで得られるもの
**できるようになること:**
- ネイティブLSPでコード補完が動作
- 関数定義にジャンプできる
- コメントアウトが一瞬で完了
- 括弧の自動補完
- エラーがリアルタイムで表示される
- **coc.nvimなしでVSCode並みの補完機能**

**どれくらい楽になるか:**
- 従来（プラグインなし）: 関数名を全て手入力、スペルミス多発
- Phase 5後: 途中まで入力すると候補が出る、Tabで補完完了（10秒→2秒）
- 「この関数どこで定義したっけ？」→ gd一発で移動（30秒→1秒）
- デバッグコメント追加: 5行選択してgc（10秒→2秒）
- **VSCodeの基本的な補完機能に到達**
- **Phase 4で移行したことで、この設定が非常にスムーズ**

#### 学習内容

1. **必要なツールのインストール**
   ```bash
   # コンパイラとツール
   sudo apt install build-essential gdb
   
   # clangdのインストール（LSP用）
   sudo apt install clangd-12
   sudo update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-12 100
   
   # Node.js（一部プラグインで必要）
   sudo apt install nodejs npm
   ```

2. **init.vimをinit.luaに移行準備**
   ```bash
   # 既存のinit.vimをバックアップ
   mv ~/.config/nvim/init.vim ~/.config/nvim/init.vim.bak
   
   # init.luaを作成
   nvim ~/.config/nvim/init.lua
   ```

3. **init.luaの基本設定**
   ```lua
   -- 基本設定
   vim.opt.number = true
   vim.opt.relativenumber = true
   vim.opt.cursorline = true
   vim.opt.showmatch = true
   vim.opt.incsearch = true
   vim.opt.hlsearch = true
   vim.opt.ignorecase = true
   vim.opt.smartcase = true
   
   -- インデント設定
   vim.opt.tabstop = 4
   vim.opt.shiftwidth = 4
   vim.opt.expandtab = true
   vim.opt.autoindent = true
   vim.opt.smartindent = true
   
   -- エンコーディング
   vim.opt.encoding = 'utf-8'
   vim.opt.fileencoding = 'utf-8'
   
   -- その他
   vim.opt.termguicolors = true
   vim.opt.wildmenu = true
   vim.cmd('syntax on')
   
   -- リーダーキー
   vim.g.mapleader = ' '
   ```

4. **lazy.nvimのインストール**
   ```lua
   -- init.luaに追加
   
   -- lazy.nvimのブートストラップ
   local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
   if not vim.loop.fs_stat(lazypath) then
     vim.fn.system({
       "git",
       "clone",
       "--filter=blob:none",
       "https://github.com/folke/lazy.nvim.git",
       "--branch=stable",
       lazypath,
     })
   end
   vim.opt.rtp:prepend(lazypath)
   
   -- プラグイン設定
   require("lazy").setup({
     -- ファイル管理
     { "preservim/nerdtree" },
     
     -- ステータスライン
     { "nvim-lualine/lualine.nvim" },
     
     -- カラースキーム
     { "crusoexia/vim-monokai" },
     
     -- 編集支援
     { "windwp/nvim-autopairs" },
     { "numToStr/Comment.nvim" },
   })
   
   -- カラースキーム設定
   vim.cmd('colorscheme monokai')
   
   -- プラグインの設定
   require('lualine').setup()
   require('nvim-autopairs').setup()
   require('Comment').setup()
   
   -- キーマッピング
   vim.keymap.set('n', '<C-n>', ':NERDTreeToggle<CR>')
   ```

5. **LSP（Language Server Protocol）の設定**
   ```lua
   -- lazy.nvimのプラグインリストに追加
   require("lazy").setup({
     -- 既存のプラグイン
     { "preservim/nerdtree" },
     { "nvim-lualine/lualine.nvim" },
     { "crusoexia/vim-monokai" },
     { "windwp/nvim-autopairs" },
     { "numToStr/Comment.nvim" },
     
     -- LSP関連
     { "neovim/nvim-lspconfig" },
     { "hrsh7th/nvim-cmp" },
     { "hrsh7th/cmp-nvim-lsp" },
     { "hrsh7th/cmp-buffer" },
     { "hrsh7th/cmp-path" },
     { "L3MON4D3/LuaSnip" },
     { "saadparwaiz1/cmp_luasnip" },
   })
   ```

6. **LSPとnvim-cmpの詳細設定**
   ```lua
   -- LSPの設定
   local lspconfig = require('lspconfig')
   local capabilities = require('cmp_nvim_lsp').default_capabilities()
   
   -- clangd（C/C++）の設定
   lspconfig.clangd.setup{
     capabilities = capabilities,
     cmd = { "clangd", "--background-index" },
     filetypes = { "c", "cpp", "objc", "objcpp" },
   }
   
   -- LSPキーマッピング
   vim.keymap.set('n', 'gd', vim.lsp.buf.definition, { desc = 'Go to definition' })
   vim.keymap.set('n', 'K', vim.lsp.buf.hover, { desc = 'Hover documentation' })
   vim.keymap.set('n', 'gr', vim.lsp.buf.references, { desc = 'Go to references' })
   vim.keymap.set('n', '<leader>rn', vim.lsp.buf.rename, { desc = 'Rename' })
   vim.keymap.set('n', '<leader>ca', vim.lsp.buf.code_action, { desc = 'Code action' })
   
   -- 補完の設定（nvim-cmp）
   local cmp = require('cmp')
   local luasnip = require('luasnip')
   
   cmp.setup({
     snippet = {
       expand = function(args)
         luasnip.lsp_expand(args.body)
       end,
     },
     mapping = cmp.mapping.preset.insert({
       ['<C-b>'] = cmp.mapping.scroll_docs(-4),
       ['<C-f>'] = cmp.mapping.scroll_docs(4),
       ['<C-Space>'] = cmp.mapping.complete(),
       ['<C-e>'] = cmp.mapping.abort(),
       ['<CR>'] = cmp.mapping.confirm({ select = true }),
       ['<Tab>'] = cmp.mapping(function(fallback)
         if cmp.visible() then
           cmp.select_next_item()
         elseif luasnip.expand_or_jumpable() then
           luasnip.expand_or_jump()
         else
           fallback()
         end
       end, { 'i', 's' }),
       ['<S-Tab>'] = cmp.mapping(function(fallback)
         if cmp.visible() then
           cmp.select_prev_item()
         elseif luasnip.jumpable(-1) then
           luasnip.jump(-1)
         else
           fallback()
         end
       end, { 'i', 's' }),
     }),
     sources = cmp.config.sources({
       { name = 'nvim_lsp' },
       { name = 'luasnip' },
     }, {
       { name = 'buffer' },
       { name = 'path' },
     })
   })
   ```

7. **便利なキーマッピング追加**
   ```lua
   -- ウィンドウ移動
   vim.keymap.set('n', '<C-h>', '<C-w>h')
   vim.keymap.set('n', '<C-j>', '<C-w>j')
   vim.keymap.set('n', '<C-k>', '<C-w>k')
   vim.keymap.set('n', '<C-l>', '<C-w>l')
   
   -- 保存とビルド
   vim.keymap.set('n', '<leader>w', ':w<CR>')
   vim.keymap.set('n', '<leader>m', ':make<CR>')
   
   -- 検索ハイライトを消す
   vim.keymap.set('n', '<leader>h', ':nohlsearch<CR>')
   ```

#### クリア条件
- [ ] Neovimでinit.luaが動作している
- [ ] lazy.nvimでプラグイン管理ができる
- [ ] コード補完が機能する（`printf`と打ってTabで候補が出る）
- [ ] 関数定義にジャンプできる（`gd`で移動）
- [ ] `gc`でコメントアウト/解除ができる
- [ ] `()`や`{}`を入力すると自動で閉じ括弧が入力される
- [ ] エラーや警告がインラインで表示される
- [ ] 以下の課題プログラムを書いて、補完機能を使いながらコーディングできる

#### 練習課題
```c
// 以下のプログラムをNeovimで作成（補完機能を活用）
#include <stdio.h>
#include <string.h>

void print_hello(const char* name) {
    printf("Hello, %s!\n", name);
}

int main() {
    char name[100];
    printf("Enter your name: ");
    scanf("%99s", name);
    print_hello(name);  // ここでgdを押して関数定義にジャンプできるか確認
    return 0;
}
```

**確認事項:**
- `printf`と入力途中で補完候補が出る
- `gd`で関数定義にジャンプできる
- `K`でホバードキュメントが表示される
- 括弧やクォートが自動で閉じる
- `:make`でコンパイルできる

---

### Phase 6: 効率的な編集とナビゲーション（目安: 2週間）

#### このフェーズで得られるもの
**できるようになること:**
- ファイル名の一部を入力するだけで目的のファイルを開ける
- プロジェクト全体から文字列を一瞬で検索
- 10個のファイルを同時に開いても迷わない
- 同じ編集を100行に一括適用（マクロ）
- 矩形選択で縦方向の編集が自在
- ウィンドウ間を思考速度で移動

**どれくらい楽になるか:**
- 従来: `src/components/ui/button/primary.c`のようなパスを覚えて入力（20秒）
- Phase 5後: `<leader>f`→`prim`と入力→Enterで開く（3秒）
- プロジェクト全体で関数呼び出し箇所を探す: 1秒で全結果表示
- 配列の初期化を100行分: マクロ記録→99回再生で10秒
- 複数行のインデント調整: 矩形選択して一括編集（30秒→5秒）
- **中規模プロジェクト（50ファイル程度）を快適に扱える**
- **VSCodeのファジーファインダーと同等以上の速度**

#### 学習内容
1. **ファジーファインダーの導入**
   ```vim
   " .vimrcに追加
   Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
   Plug 'junegunn/fzf.vim'
   
   " キーマッピング
   nnoremap <leader>f :Files<CR>
   nnoremap <leader>b :Buffers<CR>
   nnoremap <leader>g :Rg<CR>
   nnoremap <leader>l :Lines<CR>
   ```

2. **ripgrepのインストール**
   ```bash
   sudo apt install ripgrep
   ```

3. **便利なキーマッピングの追加**
   ```vim
   " ウィンドウ移動を簡単に
   nnoremap <C-h> <C-w>h
   nnoremap <C-j> <C-w>j
   nnoremap <C-k> <C-w>k
   nnoremap <C-l> <C-w>l
   
   " バッファ切り替え
   nnoremap <leader>bn :bnext<CR>
   nnoremap <leader>bp :bprev<CR>
   nnoremap <leader>bd :bdelete<CR>
   
   " 保存とビルド
   nnoremap <leader>w :w<CR>
   nnoremap <leader>m :make<CR>
   
   " 検索ハイライトを消す
   nnoremap <leader>h :nohlsearch<CR>
   ```

4. **マルチカーソル的な編集**
   - ビジュアルブロックモード（Ctrl+v）での一括編集
   - マクロの記録と再生（q + レジスタ名）

5. **バッファとタブの使い分け**
   - バッファ一覧: `:ls`
   - タブ作成: `:tabnew`
   - タブ移動: `gt`, `gT`

#### クリア条件
- [ ] `<leader>f`でファイルをファジー検索できる
- [ ] `<leader>g`でプロジェクト全体から文字列検索できる
- [ ] 複数のウィンドウ間をCtrl+hjklで移動できる
- [ ] マクロを記録して複数行に同じ編集を適用できる
- [ ] 複数のファイルを開いて、バッファ間を素早く移動できる
- [ ] Ctrl+vで矩形選択して、一括編集ができる

#### 練習課題
1. 複数のCファイルがあるプロジェクトで、特定の関数名を全ファイルから検索
2. 10行の配列初期化コードをマクロで自動生成
3. 5つのファイルを開いて、バッファ切り替えで編集

---

### Phase 6: 効率的な編集とナビゲーション（目安: 2週間）

#### このフェーズで得られるもの
**できるようになること:**
- ファイル名の一部を入力するだけで目的のファイルを開ける
- プロジェクト全体から文字列を一瞬で検索
- 10個のファイルを同時に開いても迷わない
- 同じ編集を100行に一括適用（マクロ）
- 矩形選択で縦方向の編集が自在
- ウィンドウ間を思考速度で移動

**どれくらい楽になるか:**
- 従来: `src/components/ui/button/primary.c`のようなパスを覚えて入力（20秒）
- Phase 6後: `<leader>f`→`prim`と入力→Enterで開く（3秒）
- プロジェクト全体で関数呼び出し箇所を探す: 1秒で全結果表示
- 配列の初期化を100行分: マクロ記録→99回再生で10秒
- 複数行のインデント調整: 矩形選択して一括編集（30秒→5秒）
- **中規模プロジェクト（50ファイル程度）を快適に扱える**
- **VSCodeのファジーファインダーと同等以上の速度**

#### 学習内容

1. **Telescopeのインストール（超高速ファジーファインダー）**
   ```lua
   -- lazy.nvimのプラグインリストに追加
   {
     'nvim-telescope/telescope.nvim',
     dependencies = { 'nvim-lua/plenary.nvim' }
   },
   ```

2. **ripgrepのインストール（高速検索ツール）**
   ```bash
   sudo apt install ripgrep
   ```

3. **Telescopeの設定**
   ```lua
   -- init.luaに追加
   local builtin = require('telescope.builtin')
   
   -- ファイル検索
   vim.keymap.set('n', '<leader>ff', builtin.find_files, { desc = 'Find files' })
   
   -- 文字列検索（grep）
   vim.keymap.set('n', '<leader>fg', builtin.live_grep, { desc = 'Live grep' })
   
   -- バッファ一覧
   vim.keymap.set('n', '<leader>fb', builtin.buffers, { desc = 'Buffers' })
   
   -- ヘルプ検索
   vim.keymap.set('n', '<leader>fh', builtin.help_tags, { desc = 'Help tags' })
   
   -- 最近使ったファイル
   vim.keymap.set('n', '<leader>fr', builtin.oldfiles, { desc = 'Recent files' })
   ```

4. **便利なキーマッピングの追加**
   ```lua
   -- バッファ切り替え
   vim.keymap.set('n', '<leader>bn', ':bnext<CR>', { desc = 'Next buffer' })
   vim.keymap.set('n', '<leader>bp', ':bprev<CR>', { desc = 'Previous buffer' })
   vim.keymap.set('n', '<leader>bd', ':bdelete<CR>', { desc = 'Delete buffer' })
   
   -- ウィンドウ分割
   vim.keymap.set('n', '<leader>v', ':vsplit<CR>', { desc = 'Vertical split' })
   vim.keymap.set('n', '<leader>s', ':split<CR>', { desc = 'Horizontal split' })
   ```

5. **マクロの使い方を復習**
   - `q` + レジスタ名（例: `qa`）でマクロ記録開始
   - 編集操作を実行
   - `q`で記録終了
   - `@a`で再生、`100@a`で100回再生

6. **ビジュアルブロックモードの活用**
   - `Ctrl+v`で矩形選択モード
   - `I`で先頭に挿入、`A`で末尾に追加
   - `Esc`で全行に適用

#### クリア条件
- [ ] `<leader>ff`でファイルをファジー検索できる
- [ ] `<leader>fg`でプロジェクト全体から文字列検索できる
- [ ] Telescopeのプレビューウィンドウが表示される
- [ ] 複数のウィンドウ間をCtrl+hjklで移動できる
- [ ] マクロを記録して複数行に同じ編集を適用できる
- [ ] 複数のファイルを開いて、バッファ間を素早く移動できる
- [ ] Ctrl+vで矩形選択して、一括編集ができる

#### 練習課題
1. 複数のCファイルがあるプロジェクトで、特定の関数名を全ファイルから検索
2. 10行の配列初期化コードをマクロで自動生成
3. 5つのファイルを開いて、Telescopeでバッファ切り替え

---

### Phase 7: Git統合とデバッグ環境（目安: 1-2週間）

#### このフェーズで得られるもの
**できるようになること:**
- エディタを閉じずにGit操作が完結
- 変更した行が視覚的にハイライト表示される
- 各行の最終更新者と日時を即座に確認
- コンパイルエラーを順番に修正していける
- 複数のエラーを効率的に巡回
- gdbでのデバッグをVim内で実行

**どれくらい楽になるか:**
- 従来: Vim終了→ターミナルで`git status`→`git add`→`git commit`（1分）
- Phase 6後: `:Git status`→ファイル選択→`:Git commit`で完結（15秒）
- 「誰がこの行を変更した？」→ `:Git blame`で即座に確認（10秒→2秒）
- コンパイルエラー10個: `:cnext`で次々とジャンプして修正（5分→2分）
- デバッグ: Vim内でgdb起動、ソースコードを見ながらデバッグ
- **ターミナルとエディタの往復がゼロに**
- **ワークフローが50%高速化**

#### 学習内容
1. **Git関連プラグインの追加**
   ```vim
   Plug 'tpope/vim-fugitive'           " Git操作
   Plug 'airblade/vim-gitgutter'       " Git差分表示
   
   " GitGutterの設定
   set updatetime=100
   ```

2. **vim-fugitiveの基本操作**
   - `:Git status` - Gitステータス
   - `:Git commit` - コミット
   - `:Git push` - プッシュ
   - `:Git blame` - blame表示

3. **デバッガのインストール**
   ```bash
   sudo apt install gdb
   ```

4. **QuickFixリストの活用**
   ```vim
   " QuickFixのキーマッピング
   nnoremap <leader>co :copen<CR>
   nnoremap <leader>cc :cclose<CR>
   nnoremap <leader>cn :cnext<CR>
   nnoremap <leader>cp :cprev<CR>
   ```

5. **エラー箇所へのジャンプ**
   - `:make`実行後、エラー箇所に自動ジャンプ
   - `:cnext`, `:cprev`でエラー間を移動

#### クリア条件
- [ ] GitGutterで変更箇所が表示される
- [ ] `:Git status`でGitステータスを確認できる
- [ ] `:Git blame`で各行の変更履歴を見られる
- [ ] コンパイルエラーが出た時、QuickFixリストから該当箇所にジャンプできる
- [ ] 複数のエラーを`:cnext`/`:cprev`で巡回できる
- [ ] gdbを使った基本的なデバッグができる

#### 練習課題
1. 意図的にコンパイルエラーを3つ入れて、QuickFixで修正
2. Gitで管理されているプロジェクトで、変更箇所を確認しながらコミット
3. セグフォを起こすプログラムをgdbでデバッグ

---

### Phase 7: Git統合とデバッグ環境（目安: 1-2週間）

#### このフェーズで得られるもの
**できるようになること:**
- エディタを閉じずにGit操作が完結
- 変更した行が視覚的にハイライト表示される
- 各行の最終更新者と日時を即座に確認
- コンパイルエラーを順番に修正していける
- 複数のエラーを効率的に巡回
- gdbでのデバッグをNeovim内で実行

**どれくらい楽になるか:**
- 従来: Neovim終了→ターミナルで`git status`→`git add`→`git commit`（1分）
- Phase 7後: `:Git status`→ファイル選択→`:Git commit`で完結（15秒）
- 「誰がこの行を変更した？」→ Git情報が行横に表示（10秒→即座）
- コンパイルエラー10個: `:cnext`で次々とジャンプして修正（5分→2分）
- デバッグ: Neovim内でgdb起動、ソースコードを見ながらデバッグ
- **ターミナルとエディタの往復がゼロに**
- **ワークフローが50%高速化**

#### 学習内容

1. **Git関連プラグインの追加**
   ```lua
   -- lazy.nvimのプラグインリストに追加
   {
     'lewis6991/gitsigns.nvim',
     config = function()
       require('gitsigns').setup()
     end
   },
   { 'tpope/vim-fugitive' },
   ```

2. **gitsignsの設定**
   ```lua
   require('gitsigns').setup({
     signs = {
       add = { text = '+' },
       change = { text = '~' },
       delete = { text = '_' },
       topdelete = { text = '‾' },
       changedelete = { text = '~' },
     },
     on_attach = function(bufnr)
       local gs = package.loaded.gitsigns
       
       -- ナビゲーション
       vim.keymap.set('n', ']c', function()
         if vim.wo.diff then return ']c' end
         vim.schedule(function() gs.next_hunk() end)
         return '<Ignore>'
       end, {expr=true, buffer=bufnr})
       
       vim.keymap.set('n', '[c', function()
         if vim.wo.diff then return '[c' end
         vim.schedule(function() gs.prev_hunk() end)
         return '<Ignore>'
       end, {expr=true, buffer=bufnr})
       
       -- アクション
       vim.keymap.set('n', '<leader>hs', gs.stage_hunk, {buffer=bufnr})
       vim.keymap.set('n', '<leader>hr', gs.reset_hunk, {buffer=bufnr})
       vim.keymap.set('n', '<leader>hp', gs.preview_hunk, {buffer=bufnr})
       vim.keymap.set('n', '<leader>hb', function() gs.blame_line{full=true} end, {buffer=bufnr})
     end
   })
   ```

3. **vim-fugitiveの基本操作**
   ```lua
   -- キーマッピング
   vim.keymap.set('n', '<leader>gs', ':Git<CR>', { desc = 'Git status' })
   vim.keymap.set('n', '<leader>gc', ':Git commit<CR>', { desc = 'Git commit' })
   vim.keymap.set('n', '<leader>gp', ':Git push<CR>', { desc = 'Git push' })
   vim.keymap.set('n', '<leader>gl', ':Git log<CR>', { desc = 'Git log' })
   vim.keymap.set('n', '<leader>gb', ':Git blame<CR>', { desc = 'Git blame' })
   ```

4. **QuickFixリストの活用**
   ```lua
   -- QuickFixのキーマッピング
   vim.keymap.set('n', '<leader>co', ':copen<CR>', { desc = 'Open quickfix' })
   vim.keymap.set('n', '<leader>cc', ':cclose<CR>', { desc = 'Close quickfix' })
   vim.keymap.set('n', '<leader>cn', ':cnext<CR>', { desc = 'Next quickfix' })
   vim.keymap.set('n', '<leader>cp', ':cprev<CR>', { desc = 'Previous quickfix' })
   ```

5. **診断（エラー・警告）の設定**
   ```lua
   -- 診断の表示設定
   vim.diagnostic.config({
     virtual_text = true,
     signs = true,
     update_in_insert = false,
     underline = true,
     severity_sort = true,
   })
   
   -- 診断ナビゲーション
   vim.keymap.set('n', '[d', vim.diagnostic.goto_prev, { desc = 'Previous diagnostic' })
   vim.keymap.set('n', ']d', vim.diagnostic.goto_next, { desc = 'Next diagnostic' })
   vim.keymap.set('n', '<leader>e', vim.diagnostic.open_float, { desc = 'Show diagnostic' })
   vim.keymap.set('n', '<leader>q', vim.diagnostic.setloclist, { desc = 'Diagnostic list' })
   ```

#### クリア条件
- [ ] gitsignsで変更箇所が行番号の横に表示される
- [ ] `]c`と`[c`で変更箇所間を移動できる
- [ ] `:Git`でGitステータスを確認できる
- [ ] `:Git blame`で各行の変更履歴を見られる
- [ ] コンパイルエラーが出た時、QuickFixリストから該当箇所にジャンプできる
- [ ] 複数のエラーを`:cnext`/`:cprev`で巡回できる
- [ ] LSPの診断（エラー・警告）が表示される
- [ ] `[d`と`]d`で診断間を移動できる

#### 練習課題
1. 意図的にコンパイルエラーを3つ入れて、診断機能で修正
2. Gitで管理されているプロジェクトで、変更箇所を確認しながらコミット
3. `<leader>hb`でblame情報を確認し、誰がいつ変更したかを把握

---

### Phase 8: Treesitterの導入（目安: 3-5日）

#### このフェーズで得られるもの
**できるようになること:**
- 全ての機能がキーボードショートカット一発で起動
- プロジェクト管理からデバッグまで完全統合
- 自分専用にカスタマイズされた最適な環境
- ドキュメントを見ずに操作できる筋肉記憶
- 中規模プロジェクトを一人で開発可能
- どんなLinux環境でも即座に環境再現

**どれくらい楽になるか:**
- 従来: マウス、キーボード、ターミナルを行き来（集中力が途切れる）
- Phase 7後: 全ての操作がキーボードだけで完結（フロー状態を維持）
- ファイル検索→編集→Git確認→コミットが30秒で完結
- 「この変数名、全箇所変更したい」→ LSPのリネーム機能で一括変更（5分→10秒）
- **本格的なIDEと同等の機能を獲得**
- **コーディング速度が初心者時代の3倍に**
- **純粋なコーディング時間が20%増加（ツール操作の時間が削減されるため）**

**達成感:**
- 「Vimを使いこなせている」という自信
- 他の開発者から「Vim使えるの？すごい！」と言われる
- .vimrcが自分だけの開発基盤になる

#### 学習内容
1. **最終的なプラグイン構成**
   ```vim
   call plug#begin('~/.vim/plugged')
   
   " ファイル管理
   Plug 'preservim/nerdtree'
   Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
   Plug 'junegunn/fzf.vim'
   
   " コード編集
   Plug 'neoclide/coc.nvim', {'branch': 'release'}
   Plug 'jiangmiao/auto-pairs'
   Plug 'tpope/vim-commentary'
   Plug 'tpope/vim-surround'
   
   " 表示・UI
   Plug 'vim-airline/vim-airline'
   Plug 'vim-airline/vim-airline-themes'
   Plug 'preservim/tagbar'
   Plug 'Yggdroot/indentLine'
   
   " Git統合
   Plug 'tpope/vim-fugitive'
   Plug 'airblade/vim-gitgutter'
   
   " カラースキーム
   Plug 'morhetz/gruvbox'
   
   call plug#end()
   ```

2. **作業効率化のための設定**
   ```vim
   " 自動保存（オプション）
   autocmd TextChanged,TextChangedI <buffer> silent write
   
   " ファイルタイプ別の設定
   autocmd FileType c,cpp setlocal commentstring=//\ %s
   
   " 最後のカーソル位置を記憶
   autocmd BufReadPost *
     \ if line("'\"") > 0 && line("'\"") <= line("$") |
     \   exe "normal! g`\"" |
     \ endif
   ```

3. **プロジェクトのテンプレート作成**
   ```vim
   " C言語テンプレート
   autocmd BufNewFile *.c 0r ~/.vim/templates/template.c
   ```

#### クリア条件
- [ ] 全てのプラグインが正常に動作している
- [ ] 中規模のC/C++プロジェクト（複数ファイル）を快適に編集できる
- [ ] キーボードだけで全ての操作を完結できる
- [ ] コード補完、定義ジャンプ、リファクタリングがスムーズ
- [ ] Git操作をVim内で完結できる
- [ ] 自分専用の.vimrcが100行以上になっている
- [ ] 以下の総合課題をクリアできる

#### 総合練習課題
簡単なCプロジェクトを作成：
- ヘッダーファイル（.h）とソースファイル（.c）を分離
- Makefile作成
- Gitで管理
- 関数を複数定義し、相互参照
- コメント、インデント、命名規則を統一
- コンパイル、実行、デバッグまでVim内で完結

---

## 【応用編】Neovimへの移行

### Phase 8: Treesitterの導入（目安: 3-5日）

#### このフェーズで得られるもの
**できるようになること:**
- コードの構造を理解したシンタックスハイライト
- 関数、クラス、変数が文脈に応じて色分け
- より正確なインデント
- テキストオブジェクトの賢い選択
- 複雑なネストも視覚的に理解しやすい

**どれくらい楽になるか:**
- 従来（正規表現ベース）: 文字列内の関数名もハイライトされて混乱
- Phase 8後: 「実際の関数」だけが正確にハイライト
- 長いコードを読む速度: 30%向上（構造が視覚的に明確）
- 「このカッコどこまで？」→ 色でブロックが分かる
- リファクタリング時のミス: 50%減少（構造が見えるから）
- **コードが「読める」から「理解できる」に進化**
- **他人のコードを読むストレスが激減**

#### 学習内容

1. **nvim-treesitterのインストール**
   ```lua
   -- lazy.nvimのプラグインリストに追加
   {
     'nvim-treesitter/nvim-treesitter',
     build = ':TSUpdate',
     config = function()
       require('nvim-treesitter.configs').setup({
         -- インストールする言語
         ensure_installed = { "c", "cpp", "lua", "vim", "vimdoc", "query" },
         
         -- 自動インストール
         auto_install = true,
         
         -- ハイライト設定
         highlight = {
           enable = true,
           additional_vim_regex_highlighting = false,
         },
         
         -- インデント設定
         indent = {
           enable = true
         },
       })
     end
   },
   ```

2. **Treesitterの動作確認**
   ```vim
   " Neovim内で実行
   :TSInstall c
   :TSInstall cpp
   
   " インストール状況確認
   :TSInstallInfo
   
   " 現在のバッファの構文ツリー確認
   :InspectTree
   ```

3. **従来のシンタックスハイライトとの比較**
   - C言語ファイルを開いて視覚的な違いを確認
   - 関数定義、関数呼び出し、変数が明確に区別される
   - ブロック構造が色で分かりやすくなる

#### クリア条件
- [ ] Treesitterがインストールされた
- [ ] `:TSInstallInfo`でC/C++パーサーが`✓`になっている
- [ ] より正確なシンタックスハイライトが表示される
- [ ] コードの構造を理解したハイライトになっている
- [ ] 関数定義と関数呼び出しが異なる色で表示される
- [ ] `:InspectTree`で構文ツリーが表示できる

#### 練習課題
以下のコードを開いて、Treesitterのハイライトを確認:
```c
#include <stdio.h>

// 関数定義
int calculate(int x, int y) {
    return x + y;
}

int main() {
    // 関数呼び出し
    int result = calculate(10, 20);
    printf("Result: %d\n", result);
    return 0;
}
```
- `calculate`の定義と呼び出しで色が違うか確認
- `int`, `return`などのキーワードが明確か確認

---

### Phase 9: モダンプラグインの統合（目安: 1-2週間）

#### このフェーズで得られるもの
**できるようになること:**
- Vimの全機能を維持しながら新世代へ移行
- より高速な非同期処理
- モダンなプラグインへのアクセス
- 将来の拡張性を確保

**どれくらい楽になるか:**
- 従来（Vim）: プラグイン読み込みでカクつく瞬間がある
- Phase 8後: すべての操作がスムーズ（体感で20%高速化）
- ターミナル機能がより洗練される
- **VSCode並みのレスポンス速度を獲得**
- 設定はそのまま使えるので、リスクなく移行完了

**重要な点:**
- この時点では「速くなった」程度の違い
- 真価は次のフェーズ以降で発揮される

#### 学習内容
1. **Neovimのインストール**
   ```bash
   sudo apt install neovim
   ```

2. **設定ファイルの移行**
   ```bash
   mkdir -p ~/.config/nvim
   # VimからNeovimへ設定をコピー
   cp ~/.vimrc ~/.config/nvim/init.vim
   ```

3. **Neovim起動**
   ```bash
   nvim
   ```

4. **互換性の確認**
   - 既存の.vimrc設定が動作するか確認
   - プラグインが正常に動作するか確認

#### クリア条件
- [ ] Neovimがインストールされた
- [ ] `nvim`コマンドで起動できる
- [ ] Vimで使っていた設定とプラグインが全て動作する
- [ ] `:checkhealth`で健全性チェックができる
- [ ] エラーがないか、または解決方法を理解している

---

### Phase 9: モダンプラグインの統合（目安: 1-2週間）

#### このフェーズで得られるもの
**できるようになること:**
- モダンなファイルツリー（nvim-tree）
- キーバインドのヘルプ表示（which-key）
- より美しいステータスライン
- インデントガイドの表示
- サラウンド編集（括弧の変更など）
- トラブルシューティング機能

**どれくらい楽になるか:**
- ファイルツリー: アイコン表示で直感的、Git状態も一目瞭然
- 「このキー何だっけ？」→ `<leader>`を押すとヘルプがポップアップ
- インデント階層が視覚的に分かる（ネスト深さが一目瞭然）
- `cs"'`で囲み文字を変更（ダブルクォート→シングルクォート）
- **大規模プロジェクト（500+ファイル）も快適に扱える**
- **見た目の満足度が大幅向上（モチベーション↑）**

#### 学習内容

1. **追加プラグインのインストール**
   ```lua
   -- lazy.nvimのプラグインリストに追加
   
   -- ファイルツリー（NERDTreeの代替）
   {
     "nvim-tree/nvim-tree.lua",
     dependencies = { "nvim-tree/nvim-web-devicons" },
     config = function()
       require("nvim-tree").setup()
     end
   },
   
   -- キーバインドヘルプ
   {
     "folke/which-key.nvim",
     event = "VeryLazy",
     config = function()
       require("which-key").setup()
     end
   },
   
   -- インデントガイド
   {
     "lukas-reineke/indent-blankline.nvim",
     main = "ibl",
     config = function()
       require("ibl").setup()
     end
   },
   
   -- サラウンド編集
   {
     "kylechui/nvim-surround",
     config = function()
       require("nvim-surround").setup()
     end
   },
   
   -- トラブルシューティング
   {
     "folke/trouble.nvim",
     dependencies = { "nvim-tree/nvim-web-devicons" },
   },
   ```

2. **nvim-treeの設定**
   ```lua
   -- NERDTreeの代わりにnvim-treeを使う
   vim.keymap.set('n', '<C-n>', ':NvimTreeToggle<CR>')
   vim.keymap.set('n', '<leader>e', ':NvimTreeFocus<CR>')
   
   require("nvim-tree").setup({
     view = {
       width = 30,
     },
     renderer = {
       icons = {
         show = {
           git = true,
           file = true,
           folder = true,
         },
       },
     },
   })
   ```

3. **which-keyの設定**
   ```lua
   -- リーダーキーを押した時のヘルプ
   require("which-key").setup({
     plugins = {
       spelling = {
         enabled = true,
       },
     },
   })
   
   -- グループ名の設定
   local wk = require("which-key")
   wk.register({
     f = { name = "Find" },
     g = { name = "Git" },
     h = { name = "Hunk" },
     b = { name = "Buffer" },
     c = { name = "Quickfix/Code" },
   }, { prefix = "<leader>" })
   ```

4. **Troubleの設定**
   ```lua
   vim.keymap.set("n", "<leader>xx", "<cmd>Trouble diagnostics toggle<cr>")
   vim.keymap.set("n", "<leader>xw", "<cmd>Trouble workspace_diagnostics<cr>")
   vim.keymap.set("n", "<leader>xd", "<cmd>Trouble document_diagnostics<cr>")
   vim.keymap.set("n", "<leader>xl", "<cmd>Trouble loclist<cr>")
   vim.keymap.set("n", "<leader>xq", "<cmd>Trouble quickfix<cr>")
   ```

5. **nvim-surroundの使い方**
   - `ysiw"`：単語をダブルクォートで囲む
   - `cs"'`：ダブルクォートをシングルクォートに変更
   - `ds"`：ダブルクォートを削除
   - `yss)`：行全体を括弧で囲む

#### クリア条件
- [ ] nvim-treeが起動する（Ctrl+nで表示/非表示）
- [ ] ファイルツリーにアイコンが表示される
- [ ] `<leader>`を押すとwhich-keyのヘルプが表示される
- [ ] インデントガイドが表示される
- [ ] `ysiw"`で単語を囲める
- [ ] `<leader>xx`でTroubleが起動する
- [ ] すべてのプラグインが連携して動作している

#### 練習課題
1. nvim-treeでファイル操作（作成、削除、リネーム）
2. which-keyで`<leader>`配下のキーマッピングを確認
3. nvim-surroundで文字列のクォートを変更

---

### Phase 10: デバッグ環境の構築（目安: 1週間）

#### このフェーズで得られるもの
**できるようになること:**
- より直感的な設定記述（Vim scriptより分かりやすい）
- 条件分岐やループが簡単に書ける
- 設定ファイルの実行速度が向上
- モダンなプラグインのフル活用
- 設定のモジュール化（管理が楽に）

**どれくらい楽になるか:**
- 従来（Vim script）: `set number` `set relativenumber`...（冗長）
- Phase 9後: `vim.opt.number = true`（シンプルで読みやすい）
- 複雑な条件分岐: Luaの方が5倍書きやすい
- Neovim起動時間: さらに10-20%短縮
- 設定変更の心理的ハードルが下がる（書きやすいので）
- **プログラマーとして設定ファイルを「プログラミング」できる感覚**

#### 学習内容
1. **init.luaの作成**
   ```bash
   # init.vimをバックアップ
   mv ~/.config/nvim/init.vim ~/.config/nvim/init.vim.bak
   
   # init.luaを作成
   nvim ~/.config/nvim/init.lua
   ```

2. **基本的なLua設定**
   ```lua
   -- 基本設定
   vim.opt.number = true
   vim.opt.relativenumber = true
   vim.opt.tabstop = 4
   vim.opt.shiftwidth = 4
   vim.opt.expandtab = true
   vim.opt.smartindent = true
   
   -- リーダーキー
   vim.g.mapleader = ' '
   
   -- キーマッピング
   vim.keymap.set('n', '<leader>w', ':w<CR>')
   vim.keymap.set('n', '<leader>q', ':q<CR>')
   ```

3. **プラグインマネージャーの変更（lazy.nvim）**
   ```lua
   -- lazy.nvimのインストール
   local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
   if not vim.loop.fs_stat(lazypath) then
     vim.fn.system({
       "git",
       "clone",
       "--filter=blob:none",
       "https://github.com/folke/lazy.nvim.git",
       "--branch=stable",
       lazypath,
     })
   end
   vim.opt.rtp:prepend(lazypath)
   
   -- プラグイン設定
   require("lazy").setup({
     { "folke/tokyonight.nvim" },
     { "nvim-tree/nvim-tree.lua" },
     { "nvim-lualine/lualine.nvim" },
   })
   ```

#### クリア条件
- [ ] init.luaで基本設定ができている
- [ ] Vim scriptとLuaの違いを理解した
- [ ] lazy.nvimでプラグイン管理ができる
- [ ] Luaで簡単なキーマッピングを追加できる
- [ ] 既存の機能が全てLua設定で再現できた

---

### Phase 10: ネイティブLSPの活用（目安: 1週間）

#### このフェーズで得られるもの
**できるようになること:**
- プラグインに頼らない標準機能でLSPを利用
- より正確で高速なコード補完
- インライン診断（エラーが即座に表示）
- より賢いコードアクション（自動インポートなど）
- 複数言語のLSPを統一的に管理

**どれくらい楽になるか:**
- 従来（coc.nvim）: Node.jsに依存、設定が複雑
- Phase 10後: Neovim標準機能、設定がシンプル、メモリ使用量30%減
- 補完の精度: 「使える候補」が上位に来る（学習する）
- エラー検出: 入力中にリアルタイムで赤線表示（打ち間違いに即気づく）
- 関数のシグネチャヘルプ: 引数を入力中にヒントが出る
- **JetBrains製IDEに迫る補完精度**
- **「次に何を書くべきか」が分かる感覚**

#### 学習内容
1. **nvim-lspconfig導入**
   ```lua
   -- lazy.nvimでインストール
   require("lazy").setup({
     -- 既存のプラグイン
     { "neovim/nvim-lspconfig" },
     { "hrsh7th/nvim-cmp" },
     { "hrsh7th/cmp-nvim-lsp" },
     { "hrsh7th/cmp-buffer" },
     { "hrsh7th/cmp-path" },
     { "L3MON4D3/LuaSnip" },
   })
   ```

2. **LSP設定**
   ```lua
   -- LSP設定
   local lspconfig = require('lspconfig')
   
   -- clangdの設定
   lspconfig.clangd.setup{
     cmd = { "clangd", "--background-index" },
     filetypes = { "c", "cpp", "objc", "objcpp" },
   }
   
   -- キーマッピング
   vim.keymap.set('n', 'gd', vim.lsp.buf.definition)
   vim.keymap.set('n', 'K', vim.lsp.buf.hover)
   vim.keymap.set('n', 'gr', vim.lsp.buf.references)
   vim.keymap.set('n', '<leader>rn', vim.lsp.buf.rename)
   ```

3. **補完設定（nvim-cmp）**
   ```lua
   local cmp = require('cmp')
   
   cmp.setup({
     snippet = {
       expand = function(args)
         require('luasnip').lsp_expand(args.body)
       end,
     },
     mapping = cmp.mapping.preset.insert({
       ['<C-b>'] = cmp.mapping.scroll_docs(-4),
       ['<C-f>'] = cmp.mapping.scroll_docs(4),
       ['<C-Space>'] = cmp.mapping.complete(),
       ['<CR>'] = cmp.mapping.confirm({ select = true }),
     }),
     sources = cmp.config.sources({
       { name = 'nvim_lsp' },
       { name = 'luasnip' },
     }, {
       { name = 'buffer' },
     })
   })
   ```

#### クリア条件
- [ ] ネイティブLSPでコード補完が動作する
- [ ] coc.nvimを使わずにLSP機能が使える
- [ ] 定義ジャンプ、ホバー、リネームができる
- [ ] nvim-cmpで快適な補完ができる
- [ ] LSPの診断（エラー・警告）が表示される

---

### Phase 11: Treesitterの導入（目安: 3-5日）

#### このフェーズで得られるもの
**できるようになること:**
- コードの構造を理解したシンタックスハイライト
- 関数、クラス、変数が文脈に応じて色分け
- より正確なインデント
- テキストオブジェクトの賢い選択
- 複雑なネストも視覚的に理解しやすい

**どれくらい楽になるか:**
- 従来（正規表現ベース）: 文字列内の関数名もハイライトされて混乱
- Phase 11後: 「実際の関数」だけが正確にハイライト
- 長いコードを読む速度: 30%向上（構造が視覚的に明確）
- 「このカッコどこまで？」→ 色でブロックが分かる
- リファクタリング時のミス: 50%減少（構造が見えるから）
- **コードが「読める」から「理解できる」に進化**
- **他人のコードを読むストレスが激減**

#### 学習内容
1. **nvim-treesitterのインストール**
   ```lua
   require("lazy").setup({
     -- 既存のプラグイン
     {
       "nvim-treesitter/nvim-treesitter",
       build = ":TSUpdate"
     },
   })
   ```

2. **Treesitter設定**
   ```lua
   require('nvim-treesitter.configs').setup {
     ensure_installed = { "c", "cpp", "lua", "vim" },
     highlight = {
       enable = true,
       additional_vim_regex_highlighting = false,
     },
     indent = {
       enable = true
     },
   }
   ```

3. **シンタックスハイライトの比較**
   - 従来のregexベース vs Treesitterの構造解析

#### クリア条件
- [ ] Treesitterがインストールされた
- [ ] C/C++パーサーが正常に動作する
- [ ] より正確なシンタックスハイライトが表示される
- [ ] コードの構造を理解したハイライトになっている
- [ ] `:TSInstallInfo`でインストール状況を確認できる

---

### Phase 12: モダンプラグインの導入（目安: 1-2週間）

#### このフェーズで得られるもの
**できるようになること:**
- 光速のファジーファインダー（Telescope）
- 美しく機能的なファイルツリー
- Git変更の視覚的な把握
- プレビュー付きの検索
- ポップアップウィンドウでの情報表示
- キー操作のリアルタイムヘルプ

**どれくらい楽になるか:**
- ファイル検索: fzf.vimの2倍速（体感）、プレビュー付き
- 1000ファイルのプロジェクトでも一瞬で目的のファイルへ
- 関数名の grep: 結果をその場でプレビュー、コンテキスト付き
- ファイルツリー: アイコン表示で直感的、Git状態も一目瞭然
- 「このキー何だっけ？」→ `<leader>`を押すとヘルプがポップアップ
- **大規模プロジェクト（500+ファイル）も快適に扱える**
- **VSCodeの検索速度を超える**
- **見た目の満足度が大幅向上（モチベーション↑）**

#### 学習内容
1. **Telescopeの導入（超高速ファジーファインダー）**
   ```lua
   require("lazy").setup({
     -- 既存のプラグイン
     {
       'nvim-telescope/telescope.nvim',
       dependencies = { 'nvim-lua/plenary.nvim' }
     },
   })
   
   -- キーマッピング
   local builtin = require('telescope.builtin')
   vim.keymap.set('n', '<leader>ff', builtin.find_files)
   vim.keymap.set('n', '<leader>fg', builtin.live_grep)
   vim.keymap.set('n', '<leader>fb', builtin.buffers)
   vim.keymap.set('n', '<leader>fh', builtin.help_tags)
   ```

2. **nvim-treeの導入（モダンなファイルツリー）**
   ```lua
   require("lazy").setup({
     -- 既存のプラグイン
     {
       "nvim-tree/nvim-tree.lua",
       dependencies = { "nvim-tree/nvim-web-devicons" },
     },
   })
   
   -- nvim-tree設定
   require("nvim-tree").setup()
   vim.keymap.set('n', '<leader>e', ':NvimTreeToggle<CR>')
   ```

3. **その他の便利なプラグイン**
   ```lua
   require("lazy").setup({
     -- ファイル管理・検索
     { 'nvim-telescope/telescope.nvim', dependencies = { 'nvim-lua/plenary.nvim' } },
     { "nvim-tree/nvim-tree.lua", dependencies = { "nvim-tree/nvim-web-devicons" } },
     
     -- LSP・補完
     { "neovim/nvim-lspconfig" },
     { "hrsh7th/nvim-cmp" },
     { "hrsh7th/cmp-nvim-lsp" },
     { "hrsh7th/cmp-buffer" },
     { "hrsh7th/cmp-path" },
     { "L3MON4D3/LuaSnip" },
     
     -- Treesitter
     { "nvim-treesitter/nvim-treesitter", build = ":TSUpdate" },
     
     -- UI
     { "nvim-lualine/lualine.nvim" },
     { "folke/tokyonight.nvim" },
     { "lewis6991/gitsigns.nvim" },
     
     -- 編集支援
     { "windwp/nvim-autopairs" },
     { "numToStr/Comment.nvim" },
     { "kylechui/nvim-surround" },
     
     -- デバッグ
     { "mfussenegger/nvim-dap" },
     { "rcarriga/nvim-dap-ui", dependencies = { "mfussenegger/nvim-dap" } },
   })
   ```

4. **各プラグインの基本設定**
   ```lua
   -- lualine
   require('lualine').setup {
     options = { theme = 'tokyonight' }
   }
   
   -- autopairs
   require('nvim-autopairs').setup{}
   
   -- Comment.nvim
   require('Comment').setup()
   
   -- gitsigns
   require('gitsigns').setup()
   
   -- nvim-surround
   require('nvim-surround').setup()
   ```

#### クリア条件
- [ ] Telescopeで高速なファイル検索ができる
- [ ] nvim-treeでファイルツリーを操作できる
- [ ] lualineで美しいステータスラインが表示される
- [ ] gitsignsでGit変更が視覚的に分かる
- [ ] 自動括弧補完、コメントアウトが快適に使える
- [ ] 全てのプラグインが連携して動作している

---

### Phase 13: デバッグ環境の構築（目安: 1週間）

#### このフェーズで得られるもの
**できるようになること:**
- グラフィカルなデバッガをNeovim内で使用
- ブレークポイントを視覚的に設定
- ステップ実行しながらコードを見る
- 変数の値をリアルタイム表示
- コールスタックの可視化
- ウォッチ式の評価

**どれくらい楽になるか:**
- 従来: gdbをCLIで操作、コードはVim、画面を行き来
- Phase 13後: 全てがNeovim内で統合、視線移動ゼロ
- バグ発見時間: 平均50%短縮
- セグフォの原因特定: 10分→2分
- 複雑なバグ: ステップ実行で変数を見ながら追跡
- **Visual StudioやCLionと同等のデバッグ体験**
- **printfデバッグからの完全卒業**
- **「なんで動かない？」→「ここでこの値がおかしい」と明確に**

#### 学習内容
1. **nvim-dapの設定**
   ```lua
   local dap = require('dap')
   
   -- C/C++用のデバッガ設定（gdb）
   dap.adapters.cppdbg = {
     id = 'cppdbg',
     type = 'executable',
     command = '/usr/bin/gdb',
     args = {'--interpreter=dap'}
   }
   
   dap.configurations.cpp = {
     {
       name = "Launch file",
       type = "cppdbg",
       request = "launch",
       program = function()
         return vim.fn.input('Path to executable: ', vim.fn.getcwd() .. '/', 'file')
       end,
       cwd = '${workspaceFolder}',
       stopAtEntry = true,
     },
   }
   
   dap.configurations.c = dap.configurations.cpp
   ```

2. **nvim-dap-uiの設定**
   ```lua
   local dapui = require("dapui")
   dapui.setup()
   
   -- デバッグ開始時にUIを自動で開く
   dap.listeners.after.event_initialized["dapui_config"] = function()
     dapui.open()
   end
   dap.listeners.before.event_terminated["dapui_config"] = function()
     dapui.close()
   end
   dap.listeners.before.event_exited["dapui_config"] = function()
     dapui.close()
   end
   ```

3. **デバッグ用キーマッピング**
   ```lua
   -- ブレークポイント
   vim.keymap.set('n', '<F5>', function() require('dap').continue() end)
   vim.keymap.set('n', '<F10>', function() require('dap').step_over() end)
   vim.keymap.set('n', '<F11>', function() require('dap').step_into() end)
   vim.keymap.set('n', '<F12>', function() require('dap').step_out() end)
   vim.keymap.set('n', '<leader>b', function() require('dap').toggle_breakpoint() end)
   ```

#### クリア条件
- [ ] nvim-dapでデバッグセッションを開始できる
- [ ] ブレークポイントを設定・解除できる
- [ ] ステップ実行（step over, step into, step out）ができる
- [ ] 変数の値を確認できる
- [ ] nvim-dap-uiでグラフィカルなデバッグができる
- [ ] セグメンテーションフォルトの原因を特定できる

#### 練習課題
```c
// このプログラムをデバッグで追跡
#include <stdio.h>

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int result = factorial(5);
    printf("Factorial: %d\n", result);
    return 0;
}
```
- ブレークポイントを設定
- 再帰呼び出しをステップ実行で追跡
- 各ステップでnとreturn値を確認

---

### Phase 14: プロジェクト管理と最適化（目安: 1-2週間）

#### このフェーズで得られるもの
**できるようになること:**
- プロジェクトごとに異なる設定を自動適用
- セッションの保存と復元（作業中断→即座に再開）
- CMakeプロジェクトをシームレスに操作
- 起動時間が1秒未満
- 大規模プロジェクトでも快適な動作
- チーム開発での設定共有

**どれくらい楽になるか:**
- 作業再開時間: 5分（どこまでやったっけ？）→5秒（前回の状態を完全復元）
- プロジェクト切り替え: ディレクトリ移動だけで設定が自動変更
- CMakeビルド: `<leader>cb`一発でビルド、エラーがあれば該当箇所にジャンプ
- Neovim起動: 0.5秒（遅延読み込みの最適化）
- 10,000ファイルのプロジェクトでもサクサク動作
- **企業の大規模プロジェクトに対応可能**
- **「環境構築」から「開発」へ完全シフト**
- **チームメンバーに設定を共有できる（再現性）**

#### 学習内容
1. **プロジェクトローカル設定**
   ```lua
   -- .nvim.lua（プロジェクトルートに配置）
   vim.opt_local.tabstop = 2
   vim.opt_local.shiftwidth = 2
   
   -- プロジェクト固有のビルドコマンド
   vim.keymap.set('n', '<leader>m', ':!make -C build<CR>')
   ```

2. **セッション管理**
   ```lua
   -- auto-session
   require("lazy").setup({
     {
       'rmagatti/auto-session',
       config = function()
         require("auto-session").setup {
           log_level = "error",
         }
       end
     }
   })
   ```

3. **パフォーマンス最適化**
   ```lua
   -- 起動時間の計測
   -- nvim --startuptime startup.log
   
   -- 遅延読み込みの活用
   require("lazy").setup({
     {
       "nvim-treesitter/nvim-treesitter",
       event = { "BufReadPost", "BufNewFile" },
       build = ":TSUpdate"
     },
     {
       "nvim-telescope/telescope.nvim",
       cmd = "Telescope",
       keys = {
         { "<leader>ff", "<cmd>Telescope find_files<cr>" },
         { "<leader>fg", "<cmd>Telescope live_grep<cr>" },
       }
     }
   })
   ```

4. **CMakeとの統合**
   ```lua
   require("lazy").setup({
     { "Civitasv/cmake-tools.nvim" }
   })
   
   require("cmake-tools").setup {
     cmake_command = "cmake",
     cmake_build_directory = "build",
   }
   
   vim.keymap.set('n', '<leader>cg', ':CMakeGenerate<CR>')
   vim.keymap.set('n', '<leader>cb', ':CMakeBuild<CR>')
   vim.keymap.set('n', '<leader>cr', ':CMakeRun<CR>')
   ```

#### クリア条件
- [ ] プロジェクトごとに異なる設定を適用できる
- [ ] セッションを保存・復元できる
- [ ] Neovimの起動が高速（1秒以内）
- [ ] CMakeプロジェクトをNeovim内でビルド・実行できる
- [ ] 大規模プロジェクトでも快適に作業できる

---

### Phase 15: 完全なIDE環境の完成（目安: 1週間）

#### このフェーズで得られるもの
**できるようになること:**
- プロレベルの統合開発環境
- あらゆるC/C++プロジェクトに対応
- 自分専用に最適化された究極の環境
- 他の開発者に自慢できるセットアップ
- どんなマシンでも即座に環境再現
- 新しい言語への拡張も容易

**どれくらい楽になるか:**
- **総合的な開発速度: 初心者時代の5倍**
- コーディング→ビルド→デバッグ→コミットのサイクル: 10分→2分
- 新しいプロジェクトの立ち上げ: 30分→5分
- リファクタリング: 手作業1時間→自動ツール5分
- バグ修正: 試行錯誤2時間→デバッガで30分
- **商用レベルのソフトウェア開発が可能**
- **年間で見ると数百時間の節約**

**到達レベル:**
- ✅ VSCode/CLion/Visual Studioと同等以上の機能
- ✅ より高速な動作（メモリ使用量は1/3）
- ✅ リモートサーバーでも快適（SSHだけでOK）
- ✅ 完全にカスタマイズされた自分専用IDE
- ✅ Linux環境なら3分で環境構築完了

**獲得スキル:**
- プロフェッショナルな開発フロー
- 大規模プロジェクトの管理能力
- 効率的なデバッグ技術
- Gitを使ったバージョン管理
- チーム開発への対応力

**キャリアへの影響:**
- 履歴書に「Vim/NeovimでのC/C++開発環境構築」と書ける
- 技術面接で「開発環境へのこだわり」をアピールできる
- シニアエンジニアから一目置かれる
- リモート開発、サーバーサイド開発で即戦力

#### 学習内容
1. **最終的な統合設定**
   ```lua
   -- ~/.config/nvim/init.lua の完成形
   
   -- lazy.nvimのセットアップ
   local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
   if not vim.loop.fs_stat(lazypath) then
     vim.fn.system({
       "git", "clone", "--filter=blob:none",
       "https://github.com/folke/lazy.nvim.git",
       "--branch=stable", lazypath,
     })
   end
   vim.opt.rtp:prepend(lazypath)
   
   -- 基本設定
   vim.g.mapleader = ' '
   vim.opt.number = true
   vim.opt.relativenumber = true
   vim.opt.tabstop = 4
   vim.opt.shiftwidth = 4
   vim.opt.expandtab = true
   vim.opt.smartindent = true
   vim.opt.wrap = false
   vim.opt.swapfile = false
   vim.opt.backup = false
   vim.opt.undofile = true
   vim.opt.hlsearch = false
   vim.opt.incsearch = true
   vim.opt.termguicolors = true
   vim.opt.scrolloff = 8
   vim.opt.signcolumn = "yes"
   vim.opt.updatetime = 50
   
   -- プラグイン設定を別ファイルに分割
   require("lazy").setup("plugins")
   
   -- LSP設定
   require("lsp")
   
   -- キーマッピング
   require("keymaps")
   ```

2. **設定の分割管理**
   ```
   ~/.config/nvim/
   ├── init.lua
   ├── lua/
   │   ├── plugins/
   │   │   ├── telescope.lua
   │   │   ├── treesitter.lua
   │   │   ├── lsp.lua
   │   │   └── dap.lua
   │   ├── lsp.lua
   │   └── keymaps.lua
   ```

3. **便利な機能の追加**
   ```lua
   -- Which-key（キーマッピングのヘルプ）
   require("lazy").setup({
     {
       "folke/which-key.nvim",
       event = "VeryLazy",
       init = function()
         vim.o.timeout = true
         vim.o.timeoutlen = 300
       end,
     }
   })
   
   -- Trouble（診断一覧）
   require("lazy").setup({
     {
       "folke/trouble.nvim",
       dependencies = { "nvim-tree/nvim-web-devicons" },
     }
   })
   vim.keymap.set("n", "<leader>xx", "<cmd>TroubleToggle<cr>")
   ```

4. **ワークスペース管理**
   - プロジェクトルートの自動検出
   - compile_commands.jsonの活用
   - .clangdファイルでのプロジェクト固有設定

#### 最終クリア条件
- [ ] 全ての機能が統合され、シームレスに動作する
- [ ] 設定ファイルがモジュール化され、管理しやすい
- [ ] 実際のC/C++プロジェクトで生産的に作業できる
- [ ] 以下の総合課題を完遂できる

#### 最終総合課題
**中規模C++プロジェクトの開発**

以下の機能を持つプログラムをNeovimだけで開発：
1. 複数のソースファイル（.cpp）とヘッダー（.h）
2. CMakeでのビルドシステム
3. クラス定義と継承
4. STLの使用
5. ユニットテスト
6. Git管理

要求される作業:
- Telescopeでファイル間を素早く移動
- LSPで関数定義・宣言をジャンプ
- リファクタリング（変数名変更など）
- デバッガでロジックの確認
- Gitコミットまで完結

**プロジェクト例: シンプルな連絡先管理システム**
```
contacts/
├── CMakeLists.txt
├── include/
│   ├── contact.h
│   └── contact_manager.h
├── src/
│   ├── main.cpp
│   ├── contact.cpp
│   └── contact_manager.cpp
└── tests/
    └── test_contact.cpp
```

---

## 学習のヒントとベストプラクティス

### 日々の学習習慣
1. **毎日30分以上Vimを使う**
   - 実際のコーディングで使うことが最重要
   - チュートリアルだけでは上達しない

2. **新しいコマンドを1日1つ覚える**
   - 無理に全て覚えようとしない
   - 使う頻度の高いものから習得

3. **ショートカットキーを記録する**
   - よく使うコマンドをメモに残す
   - 自分専用のチートシートを作成

### トラブルシューティング
```vim
" Vimの場合
:verbose set tabstop?  " 設定値とその設定場所を確認
:scriptnames           " 読み込まれたスクリプト一覧
:messages              " メッセージ履歴
```

```lua
-- Neovimの場合
:checkhealth           -- 環境の健全性チェック
:Lazy                  -- プラグインマネージャのUI
:LspInfo               -- LSPの状態確認
```

### コミュニティとリソース
- **公式ドキュメント**: `:help`コマンドを活用
- **GitHub**: 他の人の設定を参考にする
- **Reddit**: r/vim, r/neovim
- **Discord**: Neovim公式サーバー

### 挫折しないために
1. **完璧を求めない**: 最初は基本操作だけで十分
2. **マウスを使ってもOK**: 徐々にキーボードに移行
3. **IDEと併用**: 慣れるまで両方使うのもあり
4. **焦らない**: 習得には時間がかかって当然

---

## 各フェーズの所要時間まとめ

## 各フェーズの所要時間まとめ

| フェーズ | 期間 | 累積時間 | 到達レベル |
|---------|------|----------|-----------|
| Phase 1 | 1-2週間 | 1-2週間 | テキストエディタとして使える |
| Phase 2 | 1週間 | 2-3週間 | 快適なエディタ環境 |
| Phase 3 | 2-3日 | 3週間 | 拡張可能な基盤 |
| Phase 4 | 2週間 | 5週間 | 基本的なIDE機能（VSCode基本レベル） |
| Phase 5 | 2週間 | 7週間 | 効率的な開発環境 |
| Phase 6 | 1-2週間 | 8-9週間 | Git統合・デバッグ対応 |
| Phase 7 | 1-2週間 | 10-11週間 | **Vimでの完成形（実用レベル）** |
| Phase 8 | 2-3日 | 10-11週間 | Neovimへの移行 |
| Phase 9 | 1週間 | 11-12週間 | Lua設定の習得 |
| Phase 10 | 1週間 | 12-13週間 | ネイティブLSP活用 |
| Phase 11 | 3-5日 | 13週間 | Treesitterによる正確な解析 |
| Phase 12 | 1-2週間 | 14-15週間 | モダンプラグイン統合 |
| Phase 13 | 1週間 | 15-16週間 | グラフィカルデバッグ |
| Phase 14 | 1-2週間 | 16-18週間 | プロジェクト管理最適化 |
| Phase 15 | 1週間 | 17-19週間 | **完全なIDE環境（プロレベル）** |

## 開発速度の進化グラフ

```
開発速度（初心者時の何倍か）
5.0x │                                        ●Phase15
     │                                    ●
4.0x │                              ●
     │                         ●
3.0x │                   ●Phase7
     │              ●
2.0x │         ●
     │    ●Phase4
1.0x │●───┴───┴───┴───┴───┴───┴───┴───┴───┴───> 時間
     0   2   4   6   8   10  12  14  16  18週間
```

## 各マイルストーンでの実感

### Phase 4完了時（5週間後）
「お、これ使えるかも！」
- VSCodeの基本機能と同等
- 簡単なプログラムなら快適に書ける
- ただしまだマウスが恋しい瞬間もある

### Phase 7完了時（10-11週間後）
「もうVimなしでは開発できない！」
- マウスを完全に手放せる
- 中規模プロジェクトを一人で回せる
- 友人に「Vim使ってるの？すごい！」と言われる

### Phase 12完了時（14-15週間後）
「これ、VSCodeより速いかも...」
- 大規模プロジェクトも余裕
- ファイル検索がIDEより高速
- 見た目も機能も大満足

### Phase 15完了時（17-19週間後）
「これが俺の開発環境だ！」
- 完全に自分専用にカスタマイズ
- どんなプロジェクトでも対応可能
- 他のIDEには戻れない体になる

## 時間投資に対するリターン

### 初期投資（Phase 1-7: 約3ヶ月）
- **時間**: 毎日30分 × 70日 = 35時間
- **習得**: 実用レベルのVim開発環境

### 継続投資（Phase 8-15: 約2ヶ月）
- **時間**: 毎日30分 × 60日 = 30時間
- **習得**: プロレベルのNeovim IDE

### 生涯リターン
- **開発速度**: 5倍高速化
- **年間節約時間**: 約200時間（1日1時間開発する場合）
- **3ヶ月で投資回収**、以降はずっと利益
- **キャリア全体**: 数千時間の節約 + スキルとしての価値

## よくある質問

**Q: 本当にこんなに速くなるの？**
A: 個人差はありますが、Phase 15まで到達すれば開発速度は確実に3-5倍になります。特にキーボードショートカットによる操作速度とファイル検索の高速化が大きな要因です。

**Q: 途中で挫折しそう...**
A: Phase 4（5週間）まで到達すれば、実用的に使えるようになるので挫折率は大幅に下がります。最初の1ヶ月が山場です。

**Q: VSCodeから完全に乗り換えるべき？**
A: 必須ではありません。Phase 7まで到達してから判断すればOK。併用も十分アリです。

**Q: 他の言語にも使える？**
A: はい！LSPは多言語対応なので、Python、Rust、Go、TypeScriptなども同じ環境で開発できます。

**Q: サーバー開発には必須？**
A: SSHでリモート開発する場合、Vim/Neovimは圧倒的に有利です。GUIが不要で軽量なため、低帯域でも快適です。

---

## 最後に: このロードマップを完走したあなたは

✅ プロフェッショナルなC/C++開発者として通用する環境を持っている
✅ 大規模プロジェクトを効率的に扱える技術を習得している
✅ チーム開発で「環境のせいで遅い」ことが一切ない
✅ リモート開発、サーバーサイド開発で即戦力
✅ 他の開発者から一目置かれる「Vimmerスキル」を獲得

**あなたの開発人生が、このロードマップで大きく変わります。**
**最初の一歩を踏み出してみてください！**