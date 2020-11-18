LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY top_tb IS
END top_tb;
 
ARCHITECTURE behavior OF top_tb IS 
 
	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT top_mcs
	PORT (
		clk : IN std_logic;
		tx : OUT std_logic;
		rx : IN std_logic;
		reset : IN std_logic;
		lcd_rw : OUT std_logic;
		lcd_out : OUT std_logic_vector(5 downto 0);
		rgb_out : OUT std_logic_vector(2 downto 0);
		vsync : OUT std_logic;
		hsync : OUT std_logic
	);
	END COMPONENT;
    
	--Inputs
	signal clk : std_logic := '0';
	signal rx : std_logic := '0';
	signal reset : std_logic := '0';

	--Outputs
	signal tx : std_logic;
	signal lcd_rw : std_logic;
	signal lcd_out : std_logic_vector(5 downto 0);
	signal rgb_out : std_logic_vector(2 downto 0);
	signal vsync : std_logic;
	signal hsync : std_logic;

	-- Clock period definitions
	constant clk_period : time := 20 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
	uut: top_mcs PORT MAP (
		clk => clk,
		tx => tx,
		rx => rx,
		reset => reset,
		lcd_rw => lcd_rw,
		lcd_out => lcd_out,
		rgb_out => rgb_out,
		vsync => vsync,
		hsync => hsync
	);

	-- Clock process definitions
	clk_process :process
	begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
	end process;

END;
