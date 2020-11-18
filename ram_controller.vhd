library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ram_controller is

	Port (
		clk : in STD_LOGIC;
		p_wr_enaA: in STD_LOGIC;
		p_addrA : in STD_LOGIC_VECTOR (13 downto 0);
		p_data_inA : in STD_LOGIC_VECTOR (3 downto 0);
		p_addrB : in STD_LOGIC_VECTOR (13 downto 0);
		p_data_outA: out STD_LOGIC_VECTOR (3 downto 0);
		p_data_outB : out STD_LOGIC_VECTOR (3 downto 0)
	);

end ram_controller;

architecture Behavioral of ram_controller is
	
	COMPONENT memory_bank
	PORT (
		clka : IN STD_LOGIC;
		wea : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
		addra : IN STD_LOGIC_VECTOR(13 DOWNTO 0);
		dina : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
		douta : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
		clkb : IN STD_LOGIC;
		web : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
		addrb : IN STD_LOGIC_VECTOR(13 DOWNTO 0);
		dinb : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
		doutb : OUT STD_LOGIC_VECTOR(3 DOWNTO 0)
	);
	END COMPONENT;
	
	-- write enable for port A
	signal s_wea : STD_LOGIC_VECTOR(0 downto 0);
	
	-- address for port A -- always the same for each bank
	signal s_addra : STD_LOGIC_VECTOR(13 downto 0);

	-- data in for port A -- always the same for each bank
	signal s_dina : STD_LOGIC_VECTOR(3 downto 0);

	-- data out for port A
	signal s_douta : STD_LOGIC_VECTOR(3 downto 0);

	-- write enable for port B -- tied to LOW
	signal s_web : STD_LOGIC_VECTOR(0 downto 0);

	-- address for port B -- always the same for each bank
	signal s_addrb : STD_LOGIC_VECTOR(13 downto 0);

	-- data in for port B -- tied to LOW
	signal s_dinb 	: STD_LOGIC_VECTOR(3 downto 0);
	
	-- data out for port B
	signal s_doutb : STD_LOGIC_VECTOR(3 downto 0);

begin
	
	memory_bank0 : memory_bank
	PORT MAP (
		clka => clk,
		wea => s_wea,
		addra => s_addra,
		dina => s_dina,
		douta => s_douta,
		clkb => clk,
		web => s_web,
		addrb => s_addrb,
		dinb => s_dinb,
		doutb => s_doutb
	);
	
	-- disable writes from port B - VGA port
	s_web(0) <= '0';
	s_dinb <= "0000";
	s_dina <= p_data_inA;
	s_addra	<= p_addrA;
	s_addrb <= p_addrB;
	
	-- assing signals of port A according to address.
	s_wea(0) <= p_wr_enaA;
	
	p_data_outA <= s_douta;
					
	-- assing signals of port B according to address.
	p_data_outB <= s_doutb;

end Behavioral;

